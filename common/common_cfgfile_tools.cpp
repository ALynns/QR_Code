/* 1753935 计1 夏子寒*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <io.h>
#include <conio.h>
#include <experimental/filesystem>
#include <stdlib.h>
#include "../common/common_cfgfile_tools.hpp"

using namespace std;

int file_length(fstream &fp)
{
	int file_len, now_pos;

	/* 当前为错误状态则返回-1 */
	if (fp.fail())
		return -1;

	/* 取fp当前指针位置 */
	now_pos = int(fp.tellg());

	/* 将文件指针移动到最后，此时tellp的结果就是文件大小 */
	fp.seekg(0, ios::end);
	file_len = int(fp.tellp());

	/* 指针移动回函数调用前的原位置 */
	fp.seekg(now_pos, ios::beg);

	return file_len;
}

int file_resize(const char *filename, fstream &fp, int newsize)
{
	int now_pos;

	/* 当前为错误状态则返回-1 */
	if (fp.fail())
		return -1;

	/* 取fp当前指针位置 */
	now_pos = int(fp.tellg());

	/* 如果大小是负数则直接返回-1 */
	if (newsize < 0)
		return -1;

	experimental::filesystem::resize_file(filename, newsize);

	/* 如果当前文件指针超过了文件大小，则回到文件头 */
	if (now_pos > newsize)
		fp.seekg(0, ios::beg);

	return 0;
}


int find_group(fstream &fp, const char *group)
{
	int name_length, i;
	int group_place = 0;
	const int temp_size = 128;
	char *temp;

	temp = new(nothrow)char[temp_size];

	fp.clear();
	fp.seekg(0,ios::beg);

	name_length = strlen(group);

	while (fp.getline(temp, temp_size))
	{
		group_place++;
		sclear(temp);
		for (i = 0; i < int(strlen(temp)); i++)
			if (!strncmp(&temp[i], group, name_length))
			{
				fp.clear();
				fp.seekp(0, ios::beg);
				return group_place;
			}
	}

	fp.clear();
	fp.seekp(0, ios::beg);
	return -1;

}

int find_item(fstream &fp, int group_place, const char *item_name)
{
	const int temp_size = 128;
	char *temp;
	int i;

	temp = new(nothrow)char[temp_size];
	
	for (i = 0; i < group_place; i++)
	{
		while (fp.getline(temp, temp_size))
		{
			sclear(temp);
			if (temp[0] == '[')
				break;
		}
	}

	i = 0;
	while (fp.getline(temp, temp_size))
	{
		i++;
		if (temp[0] == '[')
		{
			fp.clear();
			fp.seekp(0, ios::beg);
			delete temp;
			return -1;
		}
		if (!strncmp(temp, item_name, strlen(item_name)))
		{
			fp.clear();
			fp.seekp(0, ios::beg);
			delete temp;
			return i + group_place;
		}
	}
	
	fp.clear();
	fp.seekp(0, ios::beg);
	delete temp;
	return -1;
}

int group_len(fstream &fp, int group_place)
{
	int group_length = 1, i;
	char *ch;

	fp.clear();
	fp.seekg(0, ios::beg);

	ch = new(nothrow)char[128];
	for (i = 0; i < group_place - 1; i++)
	{
		fp.getline(ch, 128);
	}
	fp.getline(ch, 128);
	while (fp.getline(ch, 128))
	{
		sclear(ch);
		if (ch[0] == '[')
			break;
		group_length++;	
	}
	return group_length;
}

int item_len(fstream &fp, int item_place)
{
	int length;
	fp.seekg(item_place, ios::beg);
	for (length = 1;; length++)
		if (fp.get() == '\n')
			break;

	return length;
}

void sclear(char *s)
{
	int i, t;
	for (i = 0; i < int(strlen(s) + 1); i++)
		if (s[i] == '#')
			s[i] = 0;
	for (i = 0; i < int(strlen(s)); i++)
	{
		if (s[i] == '[')
			t = i;
		s[i - t] = s[i];
	}
}

void gotogroup(fstream &fp, int item_place)
{
	int i;
	char *temp;
	const int temp_size = 128;

	fp.clear();
	fp.seekg(0, ios::beg);

	temp = new(nothrow)char[temp_size];

	for (i = 0; i < item_place - 1; i++)
		fp.getline(temp, temp_size);

}



int open_cfgfile(fstream &fp,const char*cfgname, int opt)
{
	switch (opt)
	{
	    case OPEN_OPT_RDONLY:
		{
			fp.open(cfgname, ios::in);
			if (fp.is_open())
				return 1;
			else
				return 0;
		}
		case OPEN_OPT_RDWR:
		{
			fp.open(cfgname, ios::in | ios::out | ios::binary);
			if (fp.is_open())
			{
				return 1;
			}
			else
			{
				fp.open(cfgname, ios::app | ios::in);
				fp.close();
				fp.open(cfgname, ios::in | ios::out | ios::binary);
				return 1;
			}
		}
	}
	return 0;
}

void close_cfgfile(fstream &fp)
{
	fp.close();
}

int group_add(fstream &fp, const char *group)
{
	fp.clear();
	fp.seekg(0, ios::beg);

	if (find_group(fp, group) == -1)
	{
		fp.clear();
		fp.seekg(0, ios::end);
		fp << "[" << group << "]" <<"\r\n";
		return 1;
	}
	else
		return 0;
}

int group_del(fstream &fp, const char *filename, const char *group_name)
{
	int group_place, group_length, i, File_Length, n = 0;
	const int temp_size = 8 * 1024;
	char *ch, *temp;

	fp.clear();
	fp.seekg(0, ios::beg);

	while (1)
	{
		group_place = find_group(fp, group_name);
		if (group_place == -1)
			break;
		else
		{
			group_length = group_len(fp, group_place);
			ch = new(nothrow)char[128];
			temp = new(nothrow)char[temp_size];
			for (i = 0; i < group_place + group_length - 1; i++)
			{
				fp.getline(ch, 128);
			}

			fp.getline(temp, temp_size, EOF);

			fp.clear();
			fp.seekg(0, ios::beg);

			for (i = 0; i < group_place - 1; i++)
				fp.getline(ch, 128);
			fp << temp << EOF;
		}
		File_Length = file_length(fp);
		file_resize(filename, fp, File_Length);
		n++;
	}
	return n;
}

int item_add(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	char *temp;
	int group_place, item_place;
	const int temp_size = 8 * 1024;

	fp.clear();
	fp.seekp(0, ios::beg);
	
	group_place=find_group(fp, group_name);
	if (group_place == -1)
		return 0;

	item_place = find_item(fp, group_place, item_name);
	if (item_place != -1)
		return 0;

	gotogroup(fp, group_place + 1);
	temp = new(nothrow)char[temp_size];
	fp.getline(temp, temp_size, EOF);
	gotogroup(fp, group_place + 1);

	fp << item_name << "=";
	switch (item_type)
	{
	    case TYPE_INT:
		{
			fp << *((int*)item_value) << "\r\n";
			break;
		}
		case TYPE_DOUBLE:
		{
			fp << *((double*)item_value) << "\r\n";
			break;
		}
		case TYPE_STRING:
		{
			fp << (char*)item_value << "\r\n";
			break;
		}
		case TYPE_CHARACTER:
		{
			fp << *((char*)item_value) << "\r\n";
			break;
		}
		case TYPE_NULL:
		{
			fp << "\r\n";
		}
	}
	getchar();
	fp << temp ;
	delete temp;
	
	return 1;
}

int item_del(fstream &fp,const char *filename, const char *group_name, const char *item_name)
{
	int item_place, group_place, n = 0;
	char *temp;
	const int temp_size = 8 * 1024;
	group_place = find_group(fp, group_name);
	item_place = find_item(fp, group_place, item_name);

	if (group_place == -1 || item_place == -1)
		return 0;
	while (find_item(fp, group_place, item_name) != -1)
	{
		fp.clear();
		fp.seekg(0, ios::beg);
		gotogroup(fp, item_place + 1);
		temp = new(nothrow)char[temp_size];
		fp.getline(temp, temp_size, EOF);
		gotogroup(fp, item_place);
		fp << temp << EOF;
		file_resize(filename, fp, file_length(fp));
		n++;
	}

}

int item_update(fstream &fp, const char *filename, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	int item_place, group_place, n = 0;
	char *temp;
	const int temp_size = 8 * 1024;
	group_place = find_group(fp, group_name);
	item_place = find_item(fp, group_place, item_name);

	if (item_place = -1)
		return 0;

	gotogroup(fp, item_place);

	fp << item_name << "=";

	switch (item_type)
	{
	    case TYPE_INT:
	    {
		    fp << *((int*)item_value) << "\r\n";
		    break;
	    }
		case TYPE_DOUBLE:
		{
			fp << *((double*)item_value) << "\r\n";
			break;
		}
		case TYPE_STRING:
		{
			fp << (char*)item_value << "\r\n";
			break;
		}
		case TYPE_CHARACTER:
		{
			fp << *((char*)item_value) << "\r\n";
			break;
		}
		case TYPE_NULL:
		{
			fp << "\r\n";
		}
	};
	return 1;
	
}

int item_get_value(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	char *ch_value;
	int group_place, item_place, i;
	const int temp_size = 128;

	group_place = find_group(fp, group_name);
	item_place = find_item(fp, group_place, item_name);

	if (group_place == -1 || item_place == -1)
		return 0;

	gotogroup(fp, item_place);

	ch_value = new(nothrow)char[temp_size];
	fp.getline(ch_value, temp_size);

	for (i = 0; i < temp_size; i++)
		if (ch_value[i] == '=')
			break;

	switch (item_type)
	{
	    case TYPE_INT:
		{
			*(int*)item_value = atoi(&ch_value[i + 1]);
			break;
		}
		case TYPE_DOUBLE:
		{
			*(double*)item_value = atof(&ch_value[i + 1]);
			break;
		}
		case TYPE_STRING:
		{
			strncpy((char*)item_value, &ch_value[i + 1], strlen(&ch_value[i + 1]));
			((char*)item_value)[strlen(&ch_value[i + 1])] = 0;
			break;
		}
		case TYPE_CHARACTER:
		{
			*(char*)item_value = ch_value[i + 1];
			break;
		}
		case TYPE_NULL:
		{
			fp << "\r\n";
			return 0;
		}
	}

	delete ch_value;
	return 1;
}





