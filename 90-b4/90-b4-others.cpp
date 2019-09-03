/* 1753935 计1 夏子寒 */
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdlib.h>
#include <cstdio>
#include"90-b4.h"
#include"../common/cmd_console_tools.h"

using namespace std;

int get_Error_correction_level()
{
	char level;
	cout << "请输入纠错等级（L、M、Q、H）：";
	cin >> level;
	switch (level)
	{
	    case 'L':
			return Level_L;
		case 'l':
			return Level_L;
		case 'M':
			return Level_M;
		case 'm':
			return Level_M;
		case 'Q':
			return Level_Q;
		case 'q':
			return Level_Q;
		case 'H':
			return Level_H;
		case 'h':
			return Level_H;
		default:
			return Level_Q;
	}
	return Level_L;
}



str::~str()
{
	delete[]s;
	delete[]code;
}
