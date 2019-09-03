/* 1753935 ¼Æ1 ÏÄ×Óº® */
#pragma once

char menu(const char*op[10], int num);
int search(int sandbox[11][11], int X, int Y, const int s, int &n, int k);
int gameover(int sandbox[11][11], int col, int row, int score, int aim, int mod);
void outputarray(int sandbox[11][11], int row, int col, int mod);
void outputarray1(int sandbox[11][11], int row, int col, int X, int Y);
void outputarray2(int sandbox[11][11], int row, int col, int s, int X, int Y);
void frame(int row, int col, int Y, int mod);
void frame1(int row, int col, int Y, int mod);
void box(int sandbox[11][11], int row, int col, int Y, int mod);
void box1(int sandbox[11][11], int row, int col, int Y, int mod);
void singlebox(int num, int r, int c, int Y, int color, int mod);
int move(int row, int col, int &X, int &Y, int sandbox[11][11], int Y1, int mod);
int box3(int sandbox[11][11], int row, int col, int s, int Y, int x0, int y0, int mod);
void setarray(int sandbox[11][11], int row, int col, int mod);
int endfun();
char inputch(const char str[], int Y);
int inputnum(const char str[], int Y, int x);
int ych(char);
char numch(int x);
char capital(char ch);
int scorefun(int n, int &score, int mod, int s, int &aim);
char fall(int sandbox[11][11], int X, int Y, int row, int col, int s, int &score, int &aim, int mod);
void outputarray3(int sandbox[11][11], int row, int col, int s, int max, int k, int mod);
int randx(int max);