#pragma once
#ifndef MACRO_H
#define MACRO_H

#define MAX_FILE_LEN 256
//宏定义部分，定义最大值//nextsym && gramma
#define LIN_MAX_LEN 256		//行长最大值
#define IDE_MAX_LEN 32		//标识符最长长度
#define STR_MAX_LEN 128		//字符串最长长度	
#define INT_MAX	2147483647	//int型最大值

#define INT		0
#define CHAR	1
#define VOID	2
#define MAIN	3
#define SWITCH	4
#define CASE	5
#define DEFAULT	6
#define IF		7
#define WHILE	8
#define SCANF	9
#define PRINTF	10
#define RETURN	11
#define CONST	12

#define ADDSYM 0
#define MULSYM 1
#define RELSYM 2
#define UNISYM 3
#define RESSYM 4
#define IDESYM 5
#define STRSYM 6
#define SYMSYM 7
#define CHASYM 8
#define ERRSYM 9

//宏定义部分//关于符号表
#define MAX_PAR_NUM		10	//函数最大参数数量
#define MAX_SYM_NUM		100	//最多容纳符号数量（包括参数）
#define MAX_FUN_NUM		25	//最多允许定义函数数量（包括main函数在内）

#define _FULL_TABLE_	-2	//函数表满返回值
#define _IN_TABLE_		-1	//函数已在表
#define _TOO_MUC_PAR_	-3	//参数过多
//#define _FULL_TABLE_	-2	//符号表已满
#define _ALR_HAS_PAR_	-1	//已有参数



#define ZERO		0		//零
#define	CONSTANT	0		//常量
#define VARIABLE	1		//变量

#define	NOTARR	0			//不是数组
#define ARR		1			//是数组

#define BUFFSIZE 1024

#endif