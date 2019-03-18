#pragma once
#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "macrodef.h"
#include "err.h"


/*--------------------------------------------------
符号表项定义
符号名：	name
符号名长度：namelen
符号种类：	kind		常量（CONSTANT）变量（VARIABLE）
符号类型：	type		整型（INT） 字符型（CHAR）
是否是数组：array		非（NOTARR） 是（ARR）
数组上界：	upbound		例：char[3] upbound=2 char upbound=0
常量值		value		常量值为该常量的值，变量的此处为0或后续赋值
相对于第一个参数（符号）的偏移量： offset（运行栈要用）
是否是确定的值：	definite	被scan时或未改变时为0不确定，被确定值赋值编为1确定
--------------------------------------------------*/
typedef struct symbolTableTerm {
	char name[IDE_MAX_LEN];
	int namelen;
	int kind;
	int type;
	int array;
	int upbound;
	int value;
	int offset;
	int definite;
}symterm;

/*--------------------------------------------------
符号表定义
符号表项的组：		sym[MAX_SYM_LEN]		//最多容纳符号数量（包括参数）
函数中参数的数量:	numofpara
已使用的项数：		used
这些参数将在运行栈中占用的空间： usespace	初始化为0
--------------------------------------------------*/
typedef struct symbolTable {
	symterm sym[MAX_SYM_NUM];
	int numofpara;
	int used;
	int usespace;
}symtable;

/*--------------------------------------------------
函数表项定义
函数名：			name
函数名长度：		namelen
函数返回值类型：	value		整型（INT）字符型（CHAR）无返回值（VOID）
符号表指针:			stp			//symbol table pointer
--------------------------------------------------*/
typedef struct functionTableTerm {
	char name[IDE_MAX_LEN];
	int namelen;
	int value;
	symtable *stp;
}funterm;

/*--------------------------------------------------
函数表定义
函数表项的组：		fun[MAX_FUN_NUM]	//最多定义函数数量（包括main）
已登录的函数数量：	used
--------------------------------------------------*/
typedef struct functionTable {
	funterm fun[MAX_FUN_NUM];
	int used;
}funtable;

funtable *newFunTable();
int searchFun(char *name, int namelen);
int insertFun(char *name, int namelen, int value);
void showFunTable();

symtable *newSymTable();
int searchSym(char *paraname, int paralen);
int searchGlobalSym(char *paraname, int paralen);
int addPara(char *paraname, int paralen, int paratype, int definite);
int addSym(char *symname, int symlen, int symkind, int symtype, int symarray, int symupbound,int symvalue, int definite);

void showCurSym();
void showGloSym();

extern funtable *ftable;
extern symtable *glosymtable;
extern symtable *cursymtable;

#endif
