/* 1753935 ��1 ���Ӻ� */
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include <cstdio>
#include"90-b4.h"
#include"../common/cmd_console_tools.h"

using namespace std;

const char *Mod = "0100";
const char *End = "0000";
const char *fillcode[2] = { "11101100","00010001" };

const int version_counter_size = 8;


/***************************************************************************
�������ƣ�binary
��    �ܣ���һ������ת��Ϊ�������������ַ�����ʽ���
���������num����ת������  y��ת����λ��
�� �� ֵ��
˵    ����
***************************************************************************/
char* dectobinary(int num, int size)
{
	int i;
	char *p, *q;
	p = new(nothrow)char[size + 1];
	q = new(nothrow)char[size + 1];
	q[0] = 0;
	_itoa(num, p, 2);
	if (int(strlen(p)) < size)
	{
		for (i = 0; i < int(size - strlen(p)); i++)
			q[i] = '0';
		q[i] = 0;
		
	}
	strcat(q, p);
	delete []p;

	return q;
}

int btod(char *binary)
{
	int d = 0;
	unsigned int len = strlen(binary);

	if (len > 32)
		return -1;  //��λ����
	len--;

	int i = 0;
	for (i = 0; i <= int(len); i++)
	{
		d += (binary[i] - '0') * (1 << (len - i));
	}

	return d;
}

/***************************************************************************
�������ƣ�coding
��    �ܣ���str�����ַ���s���з��϶�ά������ʽ�ı���
���������
�� �� ֵ��
˵    ����
***************************************************************************/
void str::coding()
{
	int i;
	char *p;

	version = version_check();

	code = new(nothrow)char[QR_VersonInfo.ncAllCodeWord * 8 + 1];
	code[0] = 0;

	strcat(code, Mod);

	p = dectobinary(strlen(s), 8);
	strcat(code, p);
	delete[]p;

	for (i = 0; i < int(strlen(s)); i++)
	{
		p = dectobinary(int(BYTE(s[i])), 8);
		strcat(code, p);
		delete[]p;
	};

	strcat(code, End);

	complement();

	ecode();

}

/***************************************************************************
�������ƣ�version_check
��    �ܣ�Ѱ���ʺϵ�ǰ����汾
���������
�� �� ֵ��
˵    ����
***************************************************************************/
int str::version_check()
{
	int L = strlen(s);
	int i;

	for (i = 0; i < 10; i++)
	{
		if (L <= QR_VersonInfo1[i].ncDataCodeWord[Level])
			break;
	}
	QR_VersonInfo = QR_VersonInfo1[i];
	return i;
}

/***************************************************************************
�������ƣ�complement
��    �ܣ�����
���������
�� �� ֵ��
˵    ����
***************************************************************************/
void str::complement()
{
	int L, i;
	L = strlen(code);
	L = L / 8;

	for (i = 0; i < (QR_VersonInfo1[version].ncDataCodeWord[Level] - L); i++)
	{
		strcat(code, fillcode[i % 2]);
	}
}

/***************************************************************************
�������ƣ�G_TO_U
��    �ܣ�һ���ַ���s����UTF-8����
���������
�� �� ֵ��
˵    ����
***************************************************************************/
char* G_TO_U(char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

/***************************************************************************
�������ƣ�
��    �ܣ����캯�������и�ֵ�ж�
���������
�� �� ֵ��
˵    ����
***************************************************************************/
str::str(char *p)
{
	if (strlen(G_TO_U(p)) > 100)
	{
		cerr << "����100�ֽ�" << endl;
		exit(-1);
	}
	s = new(nothrow)char[strlen(G_TO_U(p)) + 1];
	strcpy(s, G_TO_U(p));
	s[strlen(G_TO_U(p))] = 0;
	Level = get_Error_correction_level();
	coding();
}

/***************************************************************************
�������ƣ�
��    �ܣ�������봮���ڽ�β�������
���������
�� �� ֵ��
˵    ����
***************************************************************************/
void GetRSCodeWord(LPBYTE lpbyRSWork, int ncDataCodeWord, int ncRSCodeWord)
{
	int i, j;

	for (i = 0; i < ncDataCodeWord; ++i)
	{
		if (lpbyRSWork[0] != 0)
		{
			BYTE nExpFirst = byIntToExp[lpbyRSWork[0]];

			for (j = 0; j < ncRSCodeWord; ++j)
			{
				BYTE nExpElement = (BYTE)(((int)(byRSExp[ncRSCodeWord][j] + nExpFirst)) % 255);
				lpbyRSWork[j] = (BYTE)(lpbyRSWork[j + 1] ^ byExpToInt[nExpElement]);
			}

			for (j = ncRSCodeWord; j < ncDataCodeWord + ncRSCodeWord - 1; ++j)
				lpbyRSWork[j] = lpbyRSWork[j + 1];
		}
		else
		{
			for (j = 0; j < ncDataCodeWord + ncRSCodeWord - 1; ++j)
				lpbyRSWork[j] = lpbyRSWork[j + 1];
		}
	}

}


void str::ecode()
{
	struct group
	{
		BYTE block[2][4][150] = { 0 };//0Ϊ���ݴ���1Ϊ�����봮
		int RSlength;
	};

	LPBYTE temp;
	group g[2];

	g[0].RSlength = QR_VersonInfo.RS_BlockInfo1[Level].ncAllCodeWord - QR_VersonInfo.RS_BlockInfo1[Level].ncDataCodeWord;
	g[1].RSlength = QR_VersonInfo.RS_BlockInfo2[Level].ncAllCodeWord - QR_VersonInfo.RS_BlockInfo2[Level].ncDataCodeWord;

	char temp1[9] = { 0 };
	char *p;
	int i, j, k;

	temp = new(nothrow)BYTE[QR_VersonInfo.ncAllCodeWord + 1];
	for (i = 0; i < QR_VersonInfo.ncAllCodeWord + 1; i++)
		temp[i] = 0;

	for (i = 0; i < QR_VersonInfo.ncDataCodeWord[Level]; i++)
	{
		strncpy(temp1, &code[i * 8], 8);
		temp[i] = BYTE(btod(temp1));
	}

	k = 0;
	//��1��
	for (i = 0; i < QR_VersonInfo.RS_BlockInfo1[Level].ncRSBlock; i++)
	{
		for (j = 0; j < QR_VersonInfo.RS_BlockInfo1[Level].ncDataCodeWord; j++)
		{
			g[0].block[0][i][j] = temp[k];
			g[0].block[1][i][j] = temp[k];
			k++;

		}

		GetRSCodeWord(g[0].block[1][i], QR_VersonInfo.RS_BlockInfo1[Level].ncDataCodeWord, g[0].RSlength);

	}
	//��2��
	for (i = 0; i < QR_VersonInfo.RS_BlockInfo2[Level].ncRSBlock; i++)
	{
		for (j = 0; j < QR_VersonInfo.RS_BlockInfo2[Level].ncDataCodeWord; j++)
		{
			g[1].block[0][i][j] = temp[k];
			g[1].block[1][i][j] = temp[k];
			k++;
		}
		GetRSCodeWord(g[1].block[1][i], QR_VersonInfo.RS_BlockInfo2[Level].ncDataCodeWord, g[1].RSlength);
	}

	
	k = 0;
	for (i = 0; i < QR_VersonInfo.RS_BlockInfo1[Level].ncDataCodeWord || i < QR_VersonInfo.RS_BlockInfo2[Level].ncDataCodeWord; i++)
	{
		if (i < QR_VersonInfo.RS_BlockInfo1[Level].ncDataCodeWord)
		{
			for (j = 0; j < QR_VersonInfo.RS_BlockInfo1[Level].ncRSBlock; j++)
			{
				temp[k] = g[0].block[0][j][i];
				k++;
			}
		}
		if (i < QR_VersonInfo.RS_BlockInfo2[Level].ncDataCodeWord)
		{
			for (j = 0; j < QR_VersonInfo.RS_BlockInfo2[Level].ncRSBlock; j++)
			{
				temp[k] = g[1].block[0][j][i];
				k++;
			}
		}
	}

	for (i = 0; i < g[0].RSlength || i < g[1].RSlength; i++)
	{
		if (i < g[0].RSlength)
		{
			for (j = 0; j < QR_VersonInfo.RS_BlockInfo1[Level].ncRSBlock; j++)
			{
				temp[k] = g[0].block[1][j][i];
				k++;
			}
		}
		if (i < g[1].RSlength)
		{
			for (j = 0; j < QR_VersonInfo.RS_BlockInfo2[Level].ncRSBlock; j++)
			{
				temp[k] = g[1].block[1][j][i];
				k++;
			}
		}
	}

	code[0] = 0;
	for (i = 0; i < QR_VersonInfo.ncAllCodeWord; i++)
	{
		p = dectobinary(int(temp[i]), 8);
		strcat(code, p);
		delete[]p;
	}
	
}








