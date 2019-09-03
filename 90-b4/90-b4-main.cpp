/* 1753935 计1 夏子寒 */

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
	cout << "输入想要转换的字符串（不超过100字节,版本依据其长度自动调节,设置为旧版控制台）：";
	cin.getline(s0, 150, '\n');
	str strings(s0);
	//blankspace(10,10, strings);
	QR_Print(5, 5, strings);
	return 0;
}

