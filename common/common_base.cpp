/* 1753935 计1 夏子寒 */

#include<iostream>
#include<iomanip>
#include <conio.h>
#include"../90-b0/90-b0.h"
#include"../common/commo.h"
#include"../common/cmd_console_tools.h"

using namespace std;



char menu(const char*op[10], int num)
{
	int length = 0;
	char option[10];
	char inoption;
	int i, j;
	for (i = 0; i < num; i++)
	{
		for (j = 0; op[i][j]; j++);
		if (length < j - 1)
			length = j - 1;
		option[i] = op[i][0];
	}
	for (i = 0; i < length; i++)
		cout << "-";
	for (i = 0; i < num; i++)
		cout << endl << op[i];
	cout << endl;
	for (i = 0; i < length; i++)
		cout << "-";
	cout << endl << "[请选择]:";
	while (1)
	{
		inoption = _getche();
		if (inoption == 'q' || inoption == 'Q')
			return 0;
		if ((inoption >= '0') && (inoption <= '9'))
			return inoption;
		if ((inoption >= 'a') && (inoption <= 'z'))
			return inoption - 'a' + 1;
		if ((inoption >= 'A') && (inoption <= 'Z'))
			return inoption - 'A' + 1;
	}
	

}

int search(int sandbox[11][11], int X, int Y, const int s, int &n, int k)
{
	if (k == 5 && sandbox[Y][X] != -1)
	{
		sandbox[Y][X] = -2;
	}
	if (sandbox[Y][X] != -2)
		return n;
	else
	{
		if (s == sandbox[Y - 1][X] && k != 3)
		{
			sandbox[Y - 1][X] = -2;
			n++;
			search(sandbox, X, Y - 1, s, n, 1);
		}
		if (s == sandbox[Y][X - 1] && k != 4)
		{
			sandbox[Y][X - 1] = -2;
			n++;
			search(sandbox, X - 1, Y, s, n, 2);
		}
		if (s == sandbox[Y + 1][X] && k != 1)
		{
			sandbox[Y + 1][X] = -2;
			n++;
			search(sandbox, X, Y + 1, s, n, 3);
		}
		if (s == sandbox[Y][X + 1] && k != 2)
		{
			sandbox[Y][X + 1] = -2;
			n++;
			search(sandbox, X + 1, Y, s, n, 4);
		}
	}
	if (k == 5)
		sandbox[Y][X] = s;
	return n;
}

int gameover(int sandbox[11][11], int col, int row, int score, int aim, int mod)
{
	int i, j;
	for (i = col; i > 0; i--)
		for (j = 1; j < row + 1; j++)
		{
			if (sandbox[i][j] == -1)
				continue;
			if (sandbox[i][j] == sandbox[i - 1][j] || sandbox[i][j] == sandbox[i][j - 1] ||
				sandbox[i][j] == sandbox[i + 1][j] || sandbox[i][j] == sandbox[i][j + 1])
			{
				return 0;
			}
		}
	if (mod == 1 && score >= aim * 1000)
		return 2;
	setcolor(14, 12);
	cout << endl << "游戏结束" << endl;
	setcolor(0, 7);
	return 1;
}

void outputarray(int sandbox[11][11], int row, int col, int mod)
{
	setcursor(CURSOR_INVISIBLE);
	int r, c;
	char y = 'A';
	cout << "  |";
	for (c = 1; c < col + 1; c++)
		cout << setw(3) << c;
	cout << endl;
	cout << "--+";
	for (c = 1; c < col + 1; c++)
		cout << "---";
	cout << endl;
	for (r = 1; r < row + 1; r++)
	{
		cout << setw(2) << y << "|";
		for (c = 1; c < col + 1; c++)
		{
			if (mod != 2)
				cout << setw(3) << sandbox[r][c];
		}
		cout << endl;
		y++;
	}
}

void outputarray1(int sandbox[11][11], int row, int col, int X, int Y)
{
	setcursor(CURSOR_INVISIBLE);
	int r, c;
	char y = 'A';
	cout << "  |";
	for (c = 1; c < col + 1; c++)
		cout << setw(3) << c;
	cout << endl;
	cout << "--+";
	for (c = 1; c < col + 1; c++)
		cout << "---";
	cout << endl;
	for (r = 1; r < row + 1; r++)
	{
		cout << setw(2) << y << "|";
		for (c = 1; c < col + 1; c++)
			if (sandbox[r][c] == -2 || (c == X && r == Y))
				cout << "  *";
			else
				cout << setw(3) << sandbox[r][c];
		cout << endl;
		y++;
	}
}

void outputarray2(int sandbox[11][11], int row, int col, int s, int X, int Y)
{
	setcursor(CURSOR_INVISIBLE);
	int r, c;
	char y = 'A';
	cout << "  |";
	for (c = 1; c < col + 1; c++)
		cout << setw(3) << c;
	cout << endl;
	cout << "--+";
	for (c = 1; c < col + 1; c++)
		cout << "---";
	cout << endl;
	for (r = 1; r < row + 1; r++)
	{
		cout << setw(2) << y << "|";
		for (c = 1; c < col + 1; c++)
			if (sandbox[r][c] == -2)
			{
				setcolor(0, 14);
				cout << setw(3) << s;
				setcolor(0, 7);
			}
			else
			{
				if (sandbox[r][c] == 0 || (r == Y && c == X))
				{
					setcolor(0, 14);
					cout << setw(3) << sandbox[r][c];
					setcolor(0, 7);
				}
				else
					cout << setw(3) << sandbox[r][c];
			}
		cout << endl;
		y++;
	}
}

void frame(int row, int col, int Y, int mod)
{
	int r, c;
	const char *p[2][6] = { { "┏" ,"━━━", "┓","┃","┗","┛",},
							{ "╔" ,"═══" ,"╗","║","╚" ,"╝" } };
	setcursor(CURSOR_INVISIBLE);
	for (r = 0; r < row + 1; r++)
	{
		
		if (r == 0)
		{
			showstr(0 + mod, r + Y + mod, p[mod][0], 0, 7);
			for (c = 0; c < col; c++)
				showstr(6 * c + 2 + mod, r + Y + mod, p[mod][1], 0, 7);
			showstr(col * 6 + 2 + mod, r + Y + mod, p[mod][2], 0, 7);
			cout << endl;
		}
		if (r > 0 && r < row + 1)
		{
			for (c = 0; c < 3; c++)
			{
				showstr(0 + mod, 3 * r + Y + c - 2 + mod, p[mod][3], 0, 7);
				showch(2 + mod, 3 * r + Y + c - 2 + mod, ' ', 0, 7, 6 * col);
				showstr(6 * col + 2 + mod, 3 * r + Y + c - 2 + mod, p[mod][3], 0, 7);
			}
		}
		if (r == row)
		{
			showstr(0 + mod, 3 * r + Y + 1 + mod, p[mod][4], 0, 7);
			for (c = 0; c < col; c++)
				showstr(6 * c + 2 + mod, 3 * r + Y + 1 + mod, p[mod][1], 0, 7);
			showstr(col * 6 + 2 + mod, 3 * r + Y + 1 + mod, p[mod][5], 0, 7);
			cout << endl;
		}
	}
	setcolor(0, 7);
}

void frame1(int row, int col, int Y, int mod)
{
	int r, c, i;
	const char *p[2][11] = { { "┏", "━━━┳", "┓", "┃", "━━━┻", "┗", "┛", "━━━╋","      ┃", "┠", "┨" },
	                         { "╔", "═══╤", "╗", "║", "═══╧", "╚", "╝", "───┼","      │", "╟", "╢" } };
	for (r = 0; r < row + 1; r++)
	{
		if (r == 0)
		{
			showstr(0 + mod, r + Y + mod, p[mod][0], 7, 0);
			for (c = 0; c < col; c++)
			{
				showstr(8 * c + 2 + mod, r + Y + mod, p[mod][1], 7, 0);
				showstr(col * 8 + mod, r + Y + mod, p[mod][2], 7, 0);
				cout << endl;
			}
		}
		if (r > 0 && r < row + 1)
		{
			for (c = 0; c < 3; c++)
			{
				showstr(0 + mod, 4 * r + Y + c - 3 + mod, p[mod][3], 7, 0);
				for (i = 0; i < col; i++)
					showstr(2 + 8 * i + mod, 4 * r + Y + c - 3 + mod, p[mod][8], 7, 0);
				showstr(8 * col + mod, 4 * r + Y + c - 3 + mod, p[mod][3], 7, 0);
			}
			showstr(0 + mod, 4 * r + Y + c - 3 + mod, p[mod][9], 7, 0);
			for (i = 0; i < col; i++)
				showstr(2 + 8 * i + mod, 4 * r + Y + c - 3 + mod, p[mod][7], 7, 0);
			showstr(8 * col + mod, 4 * r + Y + c - 3 + mod, p[mod][10], 7, 0);
		}
		if (r == row)
		{
			showstr(0 + mod, 4 * r + Y + mod, p[mod][5], 7, 0);
			for (c = 0; c < col; c++)
				showstr(8 * c + 2 + mod, 4 * r + Y + mod, p[mod][4], 7, 0);
			showstr(col * 8 + mod, 4 * r + Y + mod, p[mod][6], 7, 0);
			cout << endl;
		}
	}
}

void box(int sandbox[11][11], int row, int col, int Y, int mod)
{
	int r, c, num;
	const char *p[2][6] = { { "┏" ,"━", "┓","┃","┗","┛", },
	                        { "╔" ,"═" ,"╗","║","╚" ,"╝" } };
	for (r = 0; r<row; r++)
		for (c = 0; c < col; c++)
		{
			num = sandbox[r + 1][c + 1];
			showstr(2 + mod + 6 * c, 3 * r + Y + 1 + mod, p[mod][0], num % 7 + 9, 0);
			showstr(2 + mod + 6 * c + 2, 3 * r + Y + 1 + mod, p[mod][1], num % 7 + 9, 0);
			showstr(2 + mod + 6 * c + 4, 3 * r + Y + 1 + mod, p[mod][2], num % 7 + 9, 0);
			showstr(2 + mod + 6 * c, 3 * r + Y + 2 + mod, p[mod][3], num % 7 + 9, 0);
			if (mod == 0)
				cout << setw(2) << num;
			if (mod == 1)
				cout << "★";
			showstr(2 + mod + 6 * c + 4, 3 * r + Y + 2 + mod, p[mod][3], num % 7 + 9, 0);
			showstr(2 + mod + 6 * c, 3 * r + Y + 3 + mod, p[mod][4], num % 7 + 9, 0);
			showstr(2 + mod + 6 * c + 2, 3 * r + Y + 3 + mod, p[mod][1], num % 7 + 9, 0);
			showstr(2 + mod + 6 * c + 4, 3 * r + Y + 3 + mod, p[mod][5], num % 7 + 9, 0);
		}
	gotoxy(0, Y + 3 * (r + 1));
}

void box1(int sandbox[11][11], int row, int col, int Y, int mod)
{
	int r, c, num;
	const char *p[2][6] = { { "┏" ,"━", "┓","┃","┗","┛", },
	                        { "╔" ,"═" ,"╗","║","╚" ,"╝" } };
	for (r = 0; r<row; r++)
		for (c = 0; c < col; c++)
		{
			num = sandbox[r + 1][c + 1];
			showstr(2 + 8 * c + mod, 4 * r + Y + 1 + mod, p[mod][0], num % 7 + 9, 0);
			showstr(2 + 8 * c + 2 + mod, 4 * r + Y + 1+ mod, p[mod][1] , num % 7 + 9, 0);
			showstr(2 + 8 * c + 4 + mod, 4 * r + Y + 1 + mod, p[mod][2], num % 7 + 9, 0);
			showstr(2 + 8 * c + mod, 4 * r + Y + 2 + mod, p[mod][3], num % 7 + 9, 0);
			if (mod == 0)
				cout << setw(2) << num;
			if (mod == 1)
				cout << "★";
			showstr(2 + mod + 8 * c + 4, 4 * r + Y + 2 + mod, p[mod][3], num % 7 + 9, 0);
			showstr(2 + mod + 8 * c, 4 * r + Y + 3 + mod, p[mod][4], num % 7 + 9, 0);
			showstr(2 + mod + 8 * c + 2, 4 * r + Y + 3 + mod, p[mod][1], num % 7 + 9, 0);
			showstr(2 + mod + 8 * c + 4, 4 * r + Y + 3 + mod, p[mod][5], num % 7 + 9, 0);
		}
	gotoxy(0, Y + 4 * (r + 1));
}

void singlebox(int num, int r, int c, int Y, int color, int mod)
{
	int m = 8, n = 4;
	r--;
	c--;
	if (mod == -1)
	{
		m = 6;
		n = 3;
		mod = 1;
	}
	const char *p[2][6] = { { "┏" ,"━", "┓","┃","┗","┛", },
	                        { "╔" ,"═" ,"╗","║","╚" ,"╝" } };
	showstr(2 + mod + m * c, n * r + Y + 1 + mod, p[mod][0], color, 0);
	showstr(2 + mod + m * c + 2, n * r + Y + 1 + mod, p[mod][1], color, 0);
	showstr(2 + mod + m * c + 4, n * r + Y + 1 + mod, p[mod][2], color, 0);
	showstr(2 + mod + m * c, n * r + Y + 2 + mod, p[mod][3], color, 0);
	if (mod == 0)
		cout << setw(2) << num;
	if (mod == 1 || mod == -1)
		cout << "★";
	showstr(2 + mod + m * c + 4, n * r + Y + 2 + mod, p[mod][3], color, 0);
	showstr(2 + mod + m * c, n * r + Y + 3 + mod, p[mod][4], color, 0);
	showstr(2 + mod + m * c + 2, n * r + Y + 3 + mod, p[mod][1], color, 0);
	showstr(2 + mod + m * c + 4, n * r + Y + 3 + mod, p[mod][5], color, 0);
}

int move(int row, int col, int &X, int &Y, int sandbox[11][11], int Y1, int mod)
{
	int X0, Y0, num, XM, YM, m = 8, n = 4;
	X0 = X;
	Y0 = Y;
	int r, c;

	num = sandbox[Y0][X0];
	if (mod == -1)
	{
		m = 6;
		n = 3;
	}
	int ret, maction;
	int keycode1, keycode2;

	enable_mouse();
	setcursor(CURSOR_INVISIBLE);
	while (1) 
	{
		for (c = 1; c < col + 1; c++)
			for (r = row; r > 0; r--)
				if (sandbox[r][c] == 0)
					singlebox(0, r, c, Y1, 0, 1);
		ret = read_keyboard_and_mouse(XM, YM, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT)
		{
			switch (maction) {
			case MOUSE_ONLY_MOVED:
			{
				X = (XM - 2) / m + 1;
				Y = (YM - 1 - Y1) / n + 1;
				if ((X0 <= col) && (X0 >= 0) && (Y0 <= row) && (Y0 >= 0))
				{
					if (sandbox[Y0][X0] == 0)
						singlebox(0, Y, X, Y1, 14, mod);
					else
						singlebox(num, Y0, X0, Y1, num % 7 + 9, mod);
				}
				if ((X <= col) && (X >= 0) && (Y <= row) && (Y >= 0))
				{
					if (sandbox[Y][X] == 0)
					{
						singlebox(0, Y, X, Y1, 14, mod);
					}
					else
					{
						singlebox(sandbox[Y][X], Y, X, Y1, 14, mod);
					}
				}
				break;
			}
			case MOUSE_LEFT_BUTTON_CLICK:		
			{
				X = (XM - 2) / m + 1;
				Y = (YM - 1 - Y1) / n+ 1;
				gotoxy(0, Y1 + 4 * (row + 1));
				disable_mouse();
				return 0;
			}
			case MOUSE_NO_ACTION:
			default:
				break;
			} 
		} 
		else if (ret == CCT_KEYBOARD_EVENT) 
		{
			switch (keycode1)
			{
			    case 224:
				{
					switch (keycode2)
					{
					    case KB_ARROW_UP:
					    {
						    if (Y >= 1)
						    {
							    Y = Y - 1;
						    }
						    if (Y == 0)
						    {
							    Y = row;
						     }
						    break;
					    }
						case KB_ARROW_DOWN:
						{
							if (Y <= row)
							{
								Y = Y + 1;
							}
							if (Y == row + 1)
							{
								Y = 1;
							}
							break;
						}
						case KB_ARROW_LEFT:
						{
							if (X >= 1)
							{
								X = X - 1;
							}
							if (X == 0)
							{
								X = col;
							}
							break;
						}
						case KB_ARROW_RIGHT:
						{
							if (X <= col)
							{
								X = X + 1;
							}
							if (X == col + 1)
							{
								X = 1;
							}
							break;
						}
					}
					if (sandbox[Y0][X0] == 0)
						singlebox(0, Y, X, Y1, 14, mod);
					else
						singlebox(num, Y0, X0, Y1, num % 7 + 9, mod);
					if (sandbox[Y][X] == 0)
						singlebox(0, Y, X, Y1, 14, mod);
					else
						singlebox(sandbox[Y][X], Y, X, Y1, 14, mod);
					return 1;
					break;
				}
				case 13:
				{
					gotoxy(0, Y1 + 4 * (row + 1));
					return 0;
				}
				default:
					break;
			}
		}
		break;
	} 
	return 2;
}

int box3(int sandbox[11][11], int row, int col, int s, int Y, int x0, int y0, int mod)
{
	int r, c, A;
	for (r = 1; r < row + 1; r++)
		for (c = 1; c < col + 1; c++)
		{
			if (sandbox[r][c] == -2)
				singlebox(s, r, c, Y, 14, mod);
		}

	int ret, maction;
	int keycode1, keycode2, XM, YM;

	enable_mouse();
	setcursor(CURSOR_INVISIBLE);
	while (1)
	{
		ret = read_keyboard_and_mouse(XM, YM, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT)
		{
			switch (maction) {
			case MOUSE_ONLY_MOVED:
			{
				if ((x0 != (XM - 2) / 8 + 1) || (y0 != (YM - 1 - Y) / 4 + 1))
				{
					gotoxy(0, Y + 4 * (row + 1));
					for (r = 1; r < row + 1; r++)
					{
						for (c = 1; c < col + 1; c++)
						{
							if (sandbox[r][c] == -2)
							{
								sandbox[r][c] = s;
								singlebox(s, r, c, Y, s % 7 + 9, mod);
							}
						}
					}
					disable_mouse();
					return 1;
				}
			}
			case MOUSE_LEFT_BUTTON_CLICK:
			{
				for (r = 1; r < row + 1; r++)
					for (c = 1; c < col + 1; c++)
						if (sandbox[r][c] == -2)
							sandbox[r][c] = 0;
				disable_mouse();
				return 0;
			}
			case MOUSE_NO_ACTION:
			default:
				break;
			}
		}
		else if (ret == CCT_KEYBOARD_EVENT)
		{
			switch (keycode1)
			{
			case 224:
			{
				_getch();
				gotoxy(0, Y + 4 * (row + 1));
				for (r = 1; r < row + 1; r++)
					for (c = 1; c < col + 1; c++)
						if (sandbox[r][c] == -2)
						{
							sandbox[r][c] = s;
							singlebox(s, r, c, Y, s % 7 + 9, mod);
						}
				return 1;
			}
			case 13:
			{
				for (r = 1; r < row + 1; r++)
					for (c = 1; c < col + 1; c++)
						if (sandbox[r][c] == -2)
							sandbox[r][c] = 0;
				return 0;
			}
			default:
				break;
			}
		}
		break;
	}





	while (1)
	{
		A = _getch();
		if (A == 13)
		{
			for (r = 1; r < row + 1; r++)
				for (c = 1; c < col + 1; c++)
					if (sandbox[r][c] == -2)
						sandbox[r][c] = 0;
			return 0;
		}
		else
			if (A == 0xe0)
			{
				_getch();
				gotoxy(0, Y + 4 * (row + 1));
				for (r = 1; r < row + 1; r++)
					for (c = 1; c < col + 1; c++)
						if (sandbox[r][c] == -2)
						{
							sandbox[r][c] = s;
							singlebox(s, r, c, Y, s % 7 + 9, mod);
						}
				return 1;
			}
	}
}

int scorefun(int n, int &score, int mod, int s, int &aim)
{
	if (mod == 0)
	{
		score = score + s * (n + 1) * 3;
		cout << endl << "本次得分：" << s * (n + 1) * 3 << " 总得分：" << score << " 合成目标：" << aim;
		if ((s + 1) >= aim)
			aim++;
	}
	else
	{
		score = score + n * n * 5;
	}
	return score;
}

char fall(int sandbox[11][11], int X, int Y, int row, int col, int s, int &score, int &aim, int mod)
{
	int r, c, i, n = 0, max = s, X0, Y0;
	char confirm;
	getxy(X0, Y0);
	cout << "选定坐标" << char(Y + 'A' - 1) << X << endl;
	confirm = capital(inputch("请确认是否把相邻的相同值合并到选定坐标中(Y/N/Q)：", Y0));
	
	if (confirm == 'N')
	{
		for (r = 1; r < row + 1; r++)
			for (c = 1; c < col + 1; c++)
				if (sandbox[r][c] == -2)
					sandbox[r][c] = s;
		return confirm;
	}

	if (confirm == 'Y')
	{
		if (mod == 0)
			sandbox[Y][X] = s + 1;
		else
			sandbox[Y][X] = 0;
		for (r = 1; r < row + 1; r++)
			for (c = 1; c < col + 1; c++)
				if (sandbox[r][c] == -2)
				{
					sandbox[r][c] = 0;
					n++;
				}
		scorefun(n, score, mod, s, aim);
		cout << endl << "相同值归并后的数组(不同色标识)：" << endl;
		outputarray2(sandbox, row, col, s, X, Y);
		cout << endl << "按回车键进行数组下落除0操作..." << endl;
		for (; _getch() != 13;);
		for (i = 0; i < 8; i++)
		{
			for (r = 1; r < row + 1; r++)
				for (c = 1; c < col + 1; c++)
					if (sandbox[r + 1][c] == 0)
					{
						sandbox[r + 1][c] = sandbox[r][c];
						sandbox[r][c] = 0;
					}
		}
		if (mod == 1)
		{
			int t = 0, r1;
			for (i = 0; i < 10; i++)
			{
				for (c = 1; c < col + 1; c++)
				{
					for (r = 1; r < row + 1; r++)
						if (sandbox[r][c - 1] == 0)
							t++;
					if (t == row)
					{
						for (r1 = 1; r1 < row + 1; r1++)
						{
							sandbox[r1][c - 1] = sandbox[r1][c];
							sandbox[r1][c] = 0;
						}
					}
					t = 0;
				}
			}
		}
		cout << endl << "除0后的数组(不同色标识)：" << endl;
		outputarray3(sandbox, row, col, s, max, 0, mod);

		if (mod == 0)
		{
			cout << endl << "按回车键进行新值填充..." << endl;
			for (r = 1; r < row + 1; r++)
				for (c = 1; c < col + 1; c++)
					if (sandbox[r][c] > max)
						max = sandbox[r][c];
			for (; _getch() != 13;);
			cout << "新值填充后的数组(不同色标识)：" << endl;
			outputarray3(sandbox, row, col, s, max, 1, mod);
			return confirm;
		}
		else
			return confirm;
	}
	else
		return confirm;
}

void outputarray3(int sandbox[11][11], int row, int col, int s, int max, int k, int mod)
{
	setcursor(CURSOR_INVISIBLE);
	int r, c;
	char y = 'A';
	cout << "  |";
	for (c = 1; c < col + 1; c++)
		cout << setw(3) << c;
	cout << endl;
	cout << "--+";
	for (c = 1; c < col + 1; c++)
		cout << "---";
	cout << endl;
	for (r = 1; r < row + 1; r++)
	{
		cout << setw(2) << y << "|";
		for (c = 1; c < col + 1; c++)
		{
			if (sandbox[r][c] == 0)
			{
				if (k == 1)
				{
					if (mod == 0)
					{
						sandbox[r][c] = randx(max);
						if (sandbox[r][c] > max)
						{
							c--;
							continue;
						}
					}
					else
						sandbox[r][c] = 0;

				}
				setcolor(0, 14);
				cout << setw(3) << sandbox[r][c];
				setcolor(0, 7);
			}
			else
				cout << setw(3) << sandbox[r][c];
		}
		cout << endl;
		y++;
	}
}
