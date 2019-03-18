#pragma once
#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "macrodef.h"
#include "err.h"


/*--------------------------------------------------
���ű����
��������	name
���������ȣ�namelen
�������ࣺ	kind		������CONSTANT��������VARIABLE��
�������ͣ�	type		���ͣ�INT�� �ַ��ͣ�CHAR��
�Ƿ������飺array		�ǣ�NOTARR�� �ǣ�ARR��
�����Ͻ磺	upbound		����char[3] upbound=2 char upbound=0
����ֵ		value		����ֵΪ�ó�����ֵ�������Ĵ˴�Ϊ0�������ֵ
����ڵ�һ�����������ţ���ƫ������ offset������ջҪ�ã�
�Ƿ���ȷ����ֵ��	definite	��scanʱ��δ�ı�ʱΪ0��ȷ������ȷ��ֵ��ֵ��Ϊ1ȷ��
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
���ű���
���ű�����飺		sym[MAX_SYM_LEN]		//������ɷ�������������������
�����в���������:	numofpara
��ʹ�õ�������		used
��Щ������������ջ��ռ�õĿռ䣺 usespace	��ʼ��Ϊ0
--------------------------------------------------*/
typedef struct symbolTable {
	symterm sym[MAX_SYM_NUM];
	int numofpara;
	int used;
	int usespace;
}symtable;

/*--------------------------------------------------
���������
��������			name
���������ȣ�		namelen
��������ֵ���ͣ�	value		���ͣ�INT���ַ��ͣ�CHAR���޷���ֵ��VOID��
���ű�ָ��:			stp			//symbol table pointer
--------------------------------------------------*/
typedef struct functionTableTerm {
	char name[IDE_MAX_LEN];
	int namelen;
	int value;
	symtable *stp;
}funterm;

/*--------------------------------------------------
��������
����������飺		fun[MAX_FUN_NUM]	//��ඨ�庯������������main��
�ѵ�¼�ĺ���������	used
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
