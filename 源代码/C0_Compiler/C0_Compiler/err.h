#ifndef ERR_H
#define ERR_H

#include <stdio.h>
#include <string.h>
#include "macrodef.h"
#include "nextsym.h"

//����ʱ�ʷ����﷨�������-------------------------------------------------
//index	������Ϣ				Ӣ����Ϣ
//1		�Ƿ��ַ�				invalid symbol
//2		�ַ����ڴ��ڷǷ��ַ�	invalid symbol in string
//3		ȱ��˫�����������ַ���	need double quatation mark to end a string
//4		�ַ������ڵ�ֵ���Ϸ�	invalid symbol of char
//5		ȱ�ٷֺ�				need semicolon ";"
//6		ȱ�ٵȺ�				need equal mark "="
//7		�����ִ���				wrong reserved symbol
//8		ȱ�����ͱ�����			need reserved symbol of type "int"or"char"
//9		ȱ���ҷ�����			need closing brackets "]"
//10	ȱ���Ҵ�����			need closing braces "}"
//11	ȱ���������			need left braces "{"
//12	ȱ��������				need right parentheses ")"
//13	ȱ��������				need left parentheses "("
//14	ȱ�ٱ�ʶ��				need an identifier
//15	ȱ��������			need left brackets "["
//16	ȱ��ð��				need colon ":"
//17	ȱ�ٶ���				need comma ","
//18	ȱ��main������			need reserved symbol "main"
//19	��Ҫһ������			need divisor
//20	�������				wrong symbol
//21	ȱ��main��������		need defination of main
//22	ȱ�ٵȺŻ�������		need equal mark "=" or left parentheses"("
//23	ȱ�ٵȺŻ�������		need equal mark "=" or left brackets "["
//24	ȱ�ٶ��Ż�������		need comma "," or right parentheses ")"
//25	ȱ�ٶ��Ż�������		need comma "," or left brackets "["
//26	ȱ���޷�������			need an unsigned integer
//27	ȱ������				need an integer
//28	ȱ���ַ�				need a char
//29	ȱ�ٳ���				need a constant value
//30	δ����ĺ���			using of a function without declaration
//31	Ӧʹ���з���ֵ����		should be a using of function with return value
//32	ʹ����δ����ı�ʶ��	using of a identifier without declaration 			
//33	ȱ�ٱ��ʽ				need an expression
//34	��Ҫ���ͱ��ʽ			need an int expression
//35	�����±�ֵԽ��			invalid value of index for array
//36	��ֵ����������Ͳ�ͬ	wrong type of assignment
//37	���ܸ�����ֵ������ֵ	invalid assignment to an array or constant value
//38	Case��������ʽ��һ��	different type of case and switch
//39	������������			wrong amount of parameters
//40	�������ʹ���			wrong type of parameter
//41	���붨��void mian		the return value of main must be void
//42	main������ַ�			too much symbols after main defination
//43	���������������������Ҫ�����ŵ�		wrong ending of the code, maybe need right braces "}"
//-----------------------------------------------------------------------------

//symbol table errors----------------------------------------------------------
//index		error-message		English-message
//1			������������		can't insert: declare too much functions
//2			�����ظ�����		can't insert: function having the same name has already been declared
//3			��������			this function has too much parameters
//4			����ͬ��			this function has declared a parameter having the same name
//5			������������		this function has too much declare of symbols
//6			�ظ���������		this function has declared a symbol having the same name
//7			���ű��ʼ��ʧ��	error happened when initializing symbol tables
//8			
//-----------------------------------------------------------------------------

//extern char err_file[MAX_FILE_LEN];
//extern FILE *fp_err;

void err(int);
void tableErr(int);
void printErrorNum();
#endif