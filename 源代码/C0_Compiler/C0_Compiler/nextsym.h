#pragma once
#ifndef NEXTSYM_H
#define NEXTSYM_H

#include <stdio.h>
#include <string.h>
#include "macrodef.h"
#include "err.h"

extern char buffer[LIN_MAX_LEN];	//ȫ���ַ�
extern char iden[IDE_MAX_LEN];		//��ʶ������
extern char string[STR_MAX_LEN];	//�ַ�������
extern int type;					//�洢��ȡ�����һ��������
extern int value;					//�洢��ȡ�����һ����ֵ
extern FILE *fp_read;				//���ļ�ָ��
extern int flag_read;			//�ж�ȡ���ʶ��0û����1���꣩
extern int lp;					//��ָ�루line_pointer),ָʾ����һ���������� �ַ� 
extern int last_lp;			//��һ����ָ�룬���ڳ�����ʹ��
extern char read_file[256];
extern char write_file[256];
extern int line_number;

extern int nextsym_debug;
/***********************************************
 �����ǹ������ͣ�type) �� ֵ��value����˵��ע��
 type���巽ʽ��
	0���ӷ��������+��-��
		value = ascii(char)
	1���˷��������*��/��
		value = ascii(char)
	2����ϵ�������<��<=��>��>=��!=��==)
		value = 0��1��2��3��4��5
	3:�޷���������0������0��������
		value = value_of(unsigned_int)
	4��������
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
	5:��ʶ��
		iden[]
		value = lenth of identifier
	6:�ַ���
		string[]
		value = lenth of string( with out ")
	7:�����ࣨ()[]{};,=:��
		value = ascii(char)
	8:char��(����'a')
		value = ascii(char)
	9:���������Ϸ����ͣ�
		value = -1;
 ***********************************************/

//��غ�������������//
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