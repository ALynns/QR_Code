/* 1753935 ��1 ���Ӻ� */

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <cstdio>
#include"90-b4.h"
#include"../common/cmd_console_tools.h"

using namespace std;

int main()
{
	char s0[101];
	cout << "������Ҫת�����ַ�����������100�ֽ�,�汾�����䳤���Զ�����,����Ϊ�ɰ����̨����";
	cin.getline(s0, 150, '\n');
	str strings(s0);
	//blankspace(10,10, strings);
	QR_Print(5, 5, strings);
	return 0;
}

