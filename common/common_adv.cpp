/* 1753935 计1 夏子寒 */

#include<iostream>
#include<iomanip>
#include <conio.h>
#include"../90-b0/90-b0.h"
#include"../common/commo.h"
#include"../common/cmd_console_tools.h"

using namespace std;

void setarray(int sandbox[11][11], int row, int col, int mod)
{
	int *p;
	int r, c;
	for (p = *sandbox; p - *sandbox < 121; p++)
		*p = -1;
	if (mod == 0)
	{
		for (r = 1; r < row + 1; r++)
			for (c = 1; c < col + 1; c++)
			{
				sandbox[r][c] = randx(3);
				if (sandbox[r][c] > 3)
					c--;
			}
	}
	if (mod == 1)
	{
		for (r = 1; r < row + 1; r++)
			for (c = 1; c < col + 1; c++)
			{
				sandbox[r][c] = rand() % 5 + 1;
				if (sandbox[r][c] > 5)
					c--;
			}
	}
}

int endfun()
{
	char a[3], i;
	setcolor(0, 7);
	setcursor(CURSOR_VISIBLE_NORMAL);
	cout << "输入end结束";
	while (1)
	{
		for (i = 0; i < 3; i++)
			cin >> a[i];
		for (i = 0; i < 3; i++)
			a[i] = capital(a[i]);
		if (a[0] != 'E' || a[1] != 'N' || a[2] != 'D')
			continue;
		else
			break;
	}
	system("cls");
	setconsoleborder(120, 30);
	return 0;
}

int inputnum(const char str[], int Y, const int x)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int num, X;
	getxy(X, Y);
	while (1)
	{
		gotoxy(0, Y);
		if (x == 1)
			cout << str << "     ";
		getxy(X, Y);
		gotoxy(X - 5, Y);
		cin >> num;
		if (!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入不合法，请重新输入";
			continue;
		}
		else
			break;
	}
	return num;
}

char inputch(const char str[], int Y)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	char ch;
	int X = 0;
	for (X = 0; str[X] != 0; X++);
	X--;
	while (1)
	{
		gotoxy(0, Y);
		cout << str << "     ";
		gotoxy(X, Y);
		cin >> ch;
		if (!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入不合法，请重新输入";
			continue;
		}
		else
			break;
	}
	gotoxy(0, Y + 1);
	return ch;
}


int ych(char ch)
{
	return int(ch - 'A' + 1);
}

char numch(int x)
{
	return char(x - 1 + 'a');
}

char capital(char ch)
{
	if (ch >= 'a'&&ch <= 'z')
		return ch - 32;
	else
		return ch;
}

int randx(int max)
{
	int p, r, pn, d, n;
	if (max == 3)
	{
		d = 0;
		n = 3;
	}
	if (max == 4)
	{
		d = 10;
		n = 3;
	}
	if (max == 5)
	{
		d = 25;
		n = 4;
	}
	if (max >= 6)
	{
		d = 20;
		if (max == 6)
			n = 4;
		else
			n = max - 3;
	}
	p = rand() % 100 + 1;
	pn = (100 - d) / n;
	if (p <= (100 - d))
		r = p / pn + 1;
	else
	{
		if (max == 4 || (max == 5 && p <= 90))
			r = 4;
		else
			if (max == 5 || (max == 6 && p <= 95))
				r = 5;
			else
				if (max == 6)
					r = 6;
				else
					if (p > 95)
						r = max;
					else
						if (p > 90)
							r = max - 1;
						else
							r = max - 3;
	}
	return r;
}