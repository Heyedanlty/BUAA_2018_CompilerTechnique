#pragma once
#ifndef NEXTSYM_H
#define NEXTSYM_H

#include <stdio.h>
#include <string.h>
#include "macrodef.h"
#include "err.h"

extern char buffer[LIN_MAX_LEN];	//全行字符
extern char iden[IDE_MAX_LEN];		//标识符内容
extern char string[STR_MAX_LEN];	//字符串内容
extern int type;					//存储读取完的下一个字类型
extern int value;					//存储读取玩的下一个字值
extern FILE *fp_read;				//读文件指针
extern int flag_read;			//行读取完标识（0没读完1读完）
extern int lp;					//列指针（line_pointer),指示着下一个待分析的 字符 
extern int last_lp;			//上一个列指针，用于出错处理使用
extern char read_file[256];
extern char write_file[256];
extern int line_number;

extern int nextsym_debug;
/***********************************************
 这里是关于类型（type) 和 值（value）的说明注释
 type定义方式：
	0：加法运算符（+、-）
		value = ascii(char)
	1：乘法运算符（*、/）
		value = ascii(char)
	2：关系运算符（<、<=、>、>=、!=、==)
		value = 0、1、2、3、4、5
	3:无符号整数（0、大于0的整数）
		value = value_of(unsigned_int)
	4：保留字
		0:int
		1:char
		2:void
		3:main
		4:switch
		5:case
		6:default
		7:if
		8:while
		9:scanf
		10:printf
		11:return
		12:const
	5:标识符
		iden[]
		value = lenth of identifier
	6:字符串
		string[]
		value = lenth of string( with out ")
	7:符号类（()[]{};,=:）
		value = ascii(char)
	8:char型(形如'a')
		value = ascii(char)
	9:其他（不合法类型）
		value = -1;
 ***********************************************/

//相关函数的声明部分//
int nextsym();
void judge();
void str_judge();
void num_judge();
void chr_judge();
int rsv_judge();
void iden_judge();
int isnum(char);
int islet(char);
int isnot(char);
void __nextSemicolon();
void __nextCommaOrSemicolon();
void __nextClosingBraces();
void __nextReservedSymbol();
void __nextCommaOrRightParenthesesOrSemicolon();

extern int nextsym_debug;

#endif