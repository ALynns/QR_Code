/* 1753935 计1 夏子寒 */

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include <cstdio>
#include"90-b4.h"
#include"../common/cmd_console_tools.h"

using namespace std;

const char *FI[4] = { "110001100011000","100000011001110","010000110000011","000001001010101" };
const char *V_I[2] = { "000111110010010100","001000010110111100" };

/***************************************************************************
函数名称：QR_Print
功    能：二维码生成打印
输入参数：x：起始打印坐标横坐标  y：起始打印坐标纵坐标
返 回 值：
说    明：    
***************************************************************************/

void QR_Print(int x, int y, str &s)
{

	int field[2][49][49] = { 0 };

	Position_Detection_Patterns(field, s);
	Alignment_Patterns(field, s);
	Timing_Patterns(field, s);
	Format_Information(field, s.Level, s.version);
	Version_Information(field, s.version);
	filled(field, s);
	MaskingPattern(field, s.version);

	print(field, x, y, s.version);

	
}

/***************************************************************************
函数名称：Position_Detection_Patterns
功    能：在数组中标记三个位置探测区域
输入参数：field：二维码数组
返 回 值：
说    明：
***************************************************************************/
void Position_Detection_Patterns(int field[2][49][49], str &s)
{
	Single_Position_Detection_Patterns(field, 0, 0);
	Single_Position_Detection_Patterns(field, 10 + s.version * 4, 0);
	Single_Position_Detection_Patterns(field, 0, 10 + s.version * 4);
}

/***************************************************************************
函数名称：Single_Position_Detection_Patterns
功    能：在给定坐标处的数组中标记单个位置探测区域
输入参数：field：二维码数组， x,y:位置探测区域左上角坐标
返 回 值：
说    明：
***************************************************************************/
void Single_Position_Detection_Patterns(int field[2][49][49], int x, int y)
{
	int i, j;
	for (i = 0; i < 7; i++)
	{
		switch (i)
		{
		    case 0:
			{
				for (j = 0; j < 7; j++)
				{
					field[0][j + y][i + x] = 1;
					field[1][j + y][i + x] = 1;
				}
				break;
			}
			case 1:
			{
				j = 0;
				field[0][j + y][i + x] = 1;
				field[1][j + y][i + x] = 1;
				for (j = 1; j < 6; j++)
				{
					field[0][j + y][i + x] = 0;
					field[1][j + y][i + x] = 1;
				}
				field[0][j + y][i + x] = 1;
				field[1][j + y][i + x] = 1;
				break;
			}
			case 5:
			{
				j = 0;
				field[0][j + y][i + x] = 1;
				field[1][j + y][i + x] = 1;
				for (j = 1; j < 6; j++)
				{
					field[0][j + y][i + x] = 0;
					field[1][j + y][i + x] = 1;
				}
				field[0][j + y][i + x] = 1;
				field[1][j + y][i + x] = 1;
				break;
			}
			case 6:
			{
				for (j = 0; j < 7; j++)
				{
					field[0][j + y][i + x] = 1;
					field[1][j + y][i + x] = 1;
				}
				break;
			}
			default:
			{
				j = 0;
				field[0][j + y][i + x] = 1;
				field[1][j + y][i + x] = 1;
				j = 1;
				field[0][j + y][i + x] = 0;
				field[1][j + y][i + x] = 1;
				for (j = 2; j < 5; j++)
				{
					field[0][j + y][i + x] = 1;
					field[1][j + y][i + x] = 1;
				}
				field[0][j + y][i + x] = 0;
				field[1][j + y][i + x] = 1;
				j = 6;
				field[0][j + y][i + x] = 1;
				field[1][j + y][i + x] = 1;
			}
		}
	}
}

/***************************************************************************
函数名称：Alignment_Patterns
功    能：在数组中标记所有校正区域
输入参数：field：二维码数组
返 回 值：
说    明：
***************************************************************************/
void Alignment_Patterns(int field[2][49][49], str &s)
{
	int i, k;
	if (s.version < 7)
	{
		for (k = 0; k < s.QR_VersonInfo.ncAlignPoint; k++)
		{
			for (i = 0; i < 5; i++)
			{
				field[0][s.QR_VersonInfo.nAlignPoint[k] - 2 + i][s.QR_VersonInfo.nAlignPoint[k] - 2] = 1;
				field[1][s.QR_VersonInfo.nAlignPoint[k] - 2 + i][s.QR_VersonInfo.nAlignPoint[k] - 2] = 1;
			}

			field[0][s.QR_VersonInfo.nAlignPoint[k] - 2][s.QR_VersonInfo.nAlignPoint[k] - 2 + 1] = 1;
			field[1][s.QR_VersonInfo.nAlignPoint[k] - 2][s.QR_VersonInfo.nAlignPoint[k] - 2 + 1] = 1;
			for (i = 1; i < 4; i++)
			{
				field[0][s.QR_VersonInfo.nAlignPoint[k] - 2 + i][s.QR_VersonInfo.nAlignPoint[k] - 2 + 1] = 0;
				field[1][s.QR_VersonInfo.nAlignPoint[k] - 2 + i][s.QR_VersonInfo.nAlignPoint[k] - 2 + 1] = 1;
			}
			field[0][s.QR_VersonInfo.nAlignPoint[k] - 2 + i][s.QR_VersonInfo.nAlignPoint[k] - 2 + 1] = 1;
			field[1][s.QR_VersonInfo.nAlignPoint[k] - 2 + i][s.QR_VersonInfo.nAlignPoint[k] - 2 + 1] = 1;

			field[0][s.QR_VersonInfo.nAlignPoint[k] - 2][s.QR_VersonInfo.nAlignPoint[k] - 2 + 2] = 1;
			field[1][s.QR_VersonInfo.nAlignPoint[k] - 2][s.QR_VersonInfo.nAlignPoint[k] - 2 + 2] = 1;
			field[0][s.QR_VersonInfo.nAlignPoint[k] - 2 + 1][s.QR_VersonInfo.nAlignPoint[k] - 2 + 2] = 0;
			field[1][s.QR_VersonInfo.nAlignPoint[k] - 2 + 1][s.QR_VersonInfo.nAlignPoint[k] - 2 + 2] = 1;
			field[0][s.QR_VersonInfo.nAlignPoint[k] - 2 + 2][s.QR_VersonInfo.nAlignPoint[k] - 2 + 2] = 1;
			field[1][s.QR_VersonInfo.nAlignPoint[k] - 2 + 2][s.QR_VersonInfo.nAlignPoint[k] - 2 + 2] = 1;
			field[0][s.QR_VersonInfo.nAlignPoint[k] - 2 + 3][s.QR_VersonInfo.nAlignPoint[k] - 2 + 2] = 0;
			field[1][s.QR_VersonInfo.nAlignPoint[k] - 2 + 3][s.QR_VersonInfo.nAlignPoint[k] - 2 + 2] = 1;
			field[0][s.QR_VersonInfo.nAlignPoint[k] - 2 + 4][s.QR_VersonInfo.nAlignPoint[k] - 2 + 2] = 1;
			field[1][s.QR_VersonInfo.nAlignPoint[k] - 2 + 4][s.QR_VersonInfo.nAlignPoint[k] - 2 + 2] = 1;

			field[0][s.QR_VersonInfo.nAlignPoint[k] - 2][s.QR_VersonInfo.nAlignPoint[k] - 2 + 3] = 1;
			field[1][s.QR_VersonInfo.nAlignPoint[k] - 2][s.QR_VersonInfo.nAlignPoint[k] - 2 + 3] = 1;
			for (i = 1; i < 4; i++)
			{
				field[0][s.QR_VersonInfo.nAlignPoint[k] - 2 + i][s.QR_VersonInfo.nAlignPoint[k] - 2 + 3] = 0;
				field[1][s.QR_VersonInfo.nAlignPoint[k] - 2 + i][s.QR_VersonInfo.nAlignPoint[k] - 2 + 3] = 1;

			}
			field[0][s.QR_VersonInfo.nAlignPoint[k] - 2 + i][s.QR_VersonInfo.nAlignPoint[k] - 2 + 3] = 1;
			field[1][s.QR_VersonInfo.nAlignPoint[k] - 2 + i][s.QR_VersonInfo.nAlignPoint[k] - 2 + 3] = 1;

			for (i = 0; i < 5; i++)
			{
				field[0][s.QR_VersonInfo.nAlignPoint[k] - 2 + i][s.QR_VersonInfo.nAlignPoint[k] - 2 + 4] = 1;
				field[1][s.QR_VersonInfo.nAlignPoint[k] - 2 + i][s.QR_VersonInfo.nAlignPoint[k] - 2 + 4] = 1;
			}
		}
	}
	else
	{
		int p[6][2];
		int j = 2;

		p[0][0] = 6;
		p[0][1] = s.QR_VersonInfo.nAlignPoint[0];

		p[1][0] = s.QR_VersonInfo.nAlignPoint[0];
		p[1][1] =  6;

		for (k = 0; k < s.QR_VersonInfo.ncAlignPoint; k++)
		{
			for (i = 0; i < s.QR_VersonInfo.ncAlignPoint; i++)
			{
				p[j][0] = s.QR_VersonInfo.nAlignPoint[i];
				p[j][1] = s.QR_VersonInfo.nAlignPoint[k];
				j++;
			}		
		}

		for (k = 0; k < 6; k++)
		{
			for (i = 0; i < 5; i++)
			{
				field[0][p[k][1] - 2 + i][p[k][0] - 2] = 1;
				field[1][p[k][1] - 2 + i][p[k][0] - 2] = 1;
			}

			field[0][p[k][1] - 2][p[k][0] - 2 + 1] = 1;
			field[1][p[k][1] - 2][p[k][0] - 2 + 1] = 1;
			for (i = 1; i < 4; i++)
			{
				field[0][p[k][1] - 2 + i][p[k][0] - 2 + 1] = 0;
				field[1][p[k][1] - 2 + i][p[k][0] - 2 + 1] = 1;
			}

			field[0][p[k][1] - 2 + i][p[k][0] - 2 + 1] = 1;
			field[1][p[k][1] - 2 + i][p[k][0] - 2 + 1] = 1;

			field[0][p[k][1] - 2][p[k][0] - 2 + 2] = 1;
			field[1][p[k][1] - 2][p[k][0] - 2 + 2] = 1;
			field[0][p[k][1] - 2 + 1][p[k][0] - 2 + 2] = 0;
			field[1][p[k][1] - 2 + 1][p[k][0] - 2 + 2] = 1;
			field[0][p[k][1] - 2 + 2][p[k][0] - 2 + 2] = 1;
			field[1][p[k][1] - 2 + 2][p[k][0] - 2 + 2] = 1;
			field[0][p[k][1] - 2 + 3][p[k][0] - 2 + 2] = 0;
			field[1][p[k][1] - 2 + 3][p[k][0] - 2 + 2] = 1;
			field[0][p[k][1] - 2 + 4][p[k][0] - 2 + 2] = 1;
			field[1][p[k][1] - 2 + 4][p[k][0] - 2 + 2] = 1;

			field[0][p[k][1] - 2][p[k][0] - 2 + 3] = 1;
			field[1][p[k][1] - 2][p[k][0] - 2 + 3] = 1;
			for (i = 1; i < 4; i++)
			{
				field[0][p[k][1] - 2 + i][p[k][0] - 2 + 3] = 0;
				field[1][p[k][1] - 2 + i][p[k][0] - 2 + 3] = 1;
			}
			field[0][p[k][1] - 2 + i][p[k][0] - 2 + 3] = 1;
			field[1][p[k][1] - 2 + i][p[k][0] - 2 + 3] = 1;

			for (i = 0; i < 5; i++)
			{
				field[0][p[k][1] - 2 + i][p[k][0] - 2 + 4] = 1;
				field[1][p[k][1] - 2 + i][p[k][0] - 2 + 4] = 1;
			}
		}
	}
}

void blankspace(int x, int y, int version)
{
	setconsoleborder(90, 50);
	setfontsize("新宋体", 12);
	int modules = 17 + 4 * version + 8;
	int i;
	for (i = 0; i < modules; i++)
		showch(0, y - 2 + i, ' ', COLOR_HWHITE, COLOR_BLACK, modules * 2);
}

/***************************************************************************
函数名称：Alignment_Patterns
功    能：在数组中标记所有定位区域
输入参数：field：二维码数组
返 回 值：
说    明：
***************************************************************************/
void Timing_Patterns(int field[2][49][49], str &s)
{
	int i;
	for (i = 0; i < 4 + 4 * s.version; i++)
	{
		if (i % 2 == 0)
		{
			field[0][6][6 + i] = 1;
			field[1][6][6 + i] = 1;
		}
		else
		{
			field[0][6][6 + i] = 0;
			field[1][6][6 + i] = 1;
		}
	}
	for (i = 0; i < 4 + 4 * s.version; i++)
	{
		if (i % 2 == 0)
		{
			field[0][6 + i][6] = 1;
			field[1][6 + i][6] = 1;
		}
		else
		{
			field[0][6 + i][6] = 0;
			field[1][6 + i][6] = 1;
		}
	}
}

char* reverse(const char *s)
{
	char t;
	char *p;
	int i;
	p = new(nothrow)char[16];
	p[15] = 0;

	strcpy(p, s);
	for (i = 0; i < 7; i++)
	{
		t = p[i];
		p[i] = p[14 - i];
		p[14 - i] = t;
	}
	return p;
}

void Format_Information(int field[2][49][49], int level, int version)
{
	int i, k;

	k = 0;

	char *F_I;
	F_I = reverse(FI[level]);
	for (i = 0; i < 9; i++)
	{
		if (i == 6)
			continue;
		field[0][i][8] = F_I[k] - '0';
		field[1][i][8] = 1;
		k++;
	}
	for (i = 7; i >= 0; i--)
	{
		if (i == 6)
			continue;
		field[0][8][i] = F_I[k] - '0';
		field[1][8][i] = 1;
		k++;
	}

	k = 0;	
	for (i = 0; i < 8; i++)
	{
		field[0][8][4 * version + 16 - i] = F_I[k] - '0';
		field[1][8][4 * version + 16 - i] = 1;
		k++;
	}
	for (i = 0; i < 8; i++)
	{
		if (i == 0)
		{
			field[0][4 * version + 9 + i][8] = 1;
			field[1][4 * version + 9 + i][8] = 1;
			continue;
		}

		field[0][4 * version + 9 + i][8] = int(F_I[k] - '0');
		field[1][4 * version + 9 + i][8] = 1;
		k++;
	}
	delete[]F_I;
	
}

void Version_Information(int field[2][49][49], int version)
{
	if (version < 7)
		return;
	int i, j, k;
	
	for (i = 0,k = 0; i < 6; i++)
		for (j = 0; j < 3; j++)
		{
			field[0][i][6 + 4 * version + j] = int(V_I[version - 7][k] - '0');
			field[1][i][6 + 4 * version + j] = 1;
			k++;
		}

	for (i = 0, k = 0; i < 6; i++)
		for (j = 0; j < 3; j++)
		{
			field[0][6 + 4 * version +j][i] = int(V_I[version - 7][k] - '0');
			field[1][6 + 4 * version +j][i] = 1;
			k++;
		}
}


void filled(int field[2][49][49], str &s)
{
	int x, y, i, k, state;

	for (i = 0; i < 8; i++)
	{
		field[1][7][i] = 1;
		field[1][i][7] = 1;
		field[1][9 + 4 * s.version][i] = 1;
		field[1][9 + 4 * s.version + i][7] = 1;
		
		field[1][i][9 + 4 * s.version] = 1;
		field[1][7][9 + 4 * s.version + i] = 1;
	}

	k = 0;
	state = UP;
	x = 4 * s.version + 16;
	y = 4 * s.version + 16;

	while(1)
	{
		if (k > s.QR_VersonInfo.ncAllCodeWord * 8)
			break;
		if (x == 6)
			x--;
		if (state == UP)
		{
			for (i = 0; i < 2; i++)
			{
				if (field[1][y][x])
				{
					x--;
					continue;
				}
				field[0][y][x] = int(s.code[k] - '0');
				x--;
				k++;
			}
			if (y == 0)
			{
				state = DOWN;
				continue;
			}
			x += 2;
			y--;

		}
		if (state == DOWN)
		{
			for (i = 0; i < 2; i++)
			{
				if (field[1][y][x])
				{
					x--;
					continue;
				}
				field[0][y][x] = int(s.code[k] - '0');
				x--;
				k++;
			}
			if (y == 4 * s.version + 16)
			{
				state = UP;
				continue;
			}
			x += 2;
			y++;

		}
			
	}


}

void MaskingPattern(int field[2][49][49], int version)
{
	int i, j;
	for (i = 0; i < 4 * version + 17; i++)
		for (j = 0; j < 4 * version + 17; j++)
		{
			if (field[1][i][j] == 0 && ((i* j) % 2) + ((i* j) % 3) == 0)
			{
				field[0][i][j] = !field[0][i][j];
			}
		}
}

void print(int field[2][49][49], int x, int y, int version)
{
	int i, j;

	setconsoleborder(2 * (x + 20 + 4 * version), (24 + 4 * version));
	setfontsize("点阵字体", 12, 6);
	blankspace(x, y, version);
	for (i = 0; i < 17 + 4 * version; i++)
		for (j = 0; j < 17 + 4 * version; j++)
		{
			if (field[0][j][i] == 1)
				showch(x + 2 * i, y + j, ' ', COLOR_BLACK, COLOR_HWHITE, 2);
			else
				showch(x + 2 * i, y + j, ' ', COLOR_HWHITE, COLOR_BLACK, 2);
		}
	gotoxy(0,0);
}
