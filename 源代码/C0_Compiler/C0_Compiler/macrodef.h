#pragma once
#ifndef MACRO_H
#define MACRO_H

#define MAX_FILE_LEN 256
//�궨�岿�֣��������ֵ//nextsym && gramma
#define LIN_MAX_LEN 256		//�г����ֵ
#define IDE_MAX_LEN 32		//��ʶ�������
#define STR_MAX_LEN 128		//�ַ��������	
#define INT_MAX	2147483647	//int�����ֵ

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

//�궨�岿��//���ڷ��ű�
#define MAX_PAR_NUM		10	//��������������
#define MAX_SYM_NUM		100	//������ɷ�������������������
#define MAX_FUN_NUM		25	//��������庯������������main�������ڣ�

#define _FULL_TABLE_	-2	//������������ֵ
#define _IN_TABLE_		-1	//�������ڱ�
#define _TOO_MUC_PAR_	-3	//��������
//#define _FULL_TABLE_	-2	//���ű�����
#define _ALR_HAS_PAR_	-1	//���в���



#define ZERO		0		//��
#define	CONSTANT	0		//����
#define VARIABLE	1		//����

#define	NOTARR	0			//��������
#define ARR		1			//������

#define BUFFSIZE 1024

#endif