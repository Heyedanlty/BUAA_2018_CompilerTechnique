#ifndef ERR_H
#define ERR_H

#include <stdio.h>
#include <string.h>
#include "macrodef.h"
#include "nextsym.h"

//编译时词法错、语法错、语义错-------------------------------------------------
//index	错误信息				英文信息
//1		非法字符				invalid symbol
//2		字符串内存在非法字符	invalid symbol in string
//3		缺少双引号来结束字符串	need double quatation mark to end a string
//4		字符类型内的值不合法	invalid symbol of char
//5		缺少分号				need semicolon ";"
//6		缺少等号				need equal mark "="
//7		保留字错误				wrong reserved symbol
//8		缺少类型保留字			need reserved symbol of type "int"or"char"
//9		缺少右方括号			need closing brackets "]"
//10	缺少右大括号			need closing braces "}"
//11	缺少左大括号			need left braces "{"
//12	缺少右括号				need right parentheses ")"
//13	缺少左括号				need left parentheses "("
//14	缺少标识符				need an identifier
//15	缺少左方括号			need left brackets "["
//16	缺少冒号				need colon ":"
//17	缺少逗号				need comma ","
//18	缺少main保留字			need reserved symbol "main"
//19	需要一个因子			need divisor
//20	错误符号				wrong symbol
//21	缺少main函数定义		need defination of main
//22	缺少等号或左括号		need equal mark "=" or left parentheses"("
//23	缺少等号或左方括号		need equal mark "=" or left brackets "["
//24	缺少逗号或右括号		need comma "," or right parentheses ")"
//25	缺少逗号或左方括号		need comma "," or left brackets "["
//26	缺少无符号整数			need an unsigned integer
//27	缺少整数				need an integer
//28	缺少字符				need a char
//29	缺少常量				need a constant value
//30	未定义的函数			using of a function without declaration
//31	应使用有返回值函数		should be a using of function with return value
//32	使用了未定义的标识符	using of a identifier without declaration 			
//33	缺少表达式				need an expression
//34	需要整型表达式			need an int expression
//35	数组下标值越界			invalid value of index for array
//36	赋值语句左右类型不同	wrong type of assignment
//37	不能给数组值或常量赋值	invalid assignment to an array or constant value
//38	Case类型与表达式不一致	different type of case and switch
//39	参数数量错误			wrong amount of parameters
//40	参数类型错误			wrong type of parameter
//41	必须定义void mian		the return value of main must be void
//42	main后多余字符			too much symbols after main defination
//43	代码非正常结束，可能需要大括号等		wrong ending of the code, maybe need right braces "}"
//-----------------------------------------------------------------------------

//symbol table errors----------------------------------------------------------
//index		error-message		English-message
//1			函数声明过多		can't insert: declare too much functions
//2			函数重复声明		can't insert: function having the same name has already been declared
//3			参数过多			this function has too much parameters
//4			参数同名			this function has declared a parameter having the same name
//5			符号声明过多		this function has too much declare of symbols
//6			重复声明符号		this function has declared a symbol having the same name
//7			符号表初始化失败	error happened when initializing symbol tables
//8			
//-----------------------------------------------------------------------------

//extern char err_file[MAX_FILE_LEN];
//extern FILE *fp_err;

void err(int);
void tableErr(int);
void printErrorNum();
#endif