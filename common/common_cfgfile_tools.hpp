#pragma once

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <io.h>
#include <conio.h>
#include <experimental/filesystem>
#include <stdlib.h>

using namespace std;

enum ITEM_TYPE { TYPE_INT = 0, TYPE_DOUBLE, TYPE_STRING, TYPE_CHARACTER, TYPE_NULL }; 

#define OPEN_OPT_RDONLY		0	//以只读方式打开（打不开则返回失败）
#define OPEN_OPT_RDWR		1	//以读写方式打开（打不开文件则创建）

/* 定义插入位置：组名后第一行、组名后第一个空行、该组最后（下一组的开始） */
enum INSERT_POS_TYPE { FIRST_LINE_AFTER_GROUP = 0, FIRST_SPACE_LINE_AFTER_GROUP, BEFORE_NEXT_GROUP};

int open_cfgfile(fstream &fp,const char *cfgname, int opt);
void close_cfgfile(fstream &fp);
int group_add(fstream &fp, const char *group);
int group_del(fstream &fp, const char *filename, const char *group_name);
int item_add(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_del(fstream &fp, const char *filename, const char *group_name, const char *item_name);
int item_update(fstream &fp, const char *filename, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_get_value(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int file_length(fstream &fp);
int file_resize(const char *filename, fstream &fp, int newsize);
void sclear(char *s);

