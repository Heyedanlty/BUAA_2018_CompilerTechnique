#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "macrodef.h"
#include "err.h"		//������
#include "nextsym.h"	//�ʷ�����head
#include "gramma.h"		//�﷨����head
#include "symtable.h"	//���ű�head
#include "translate.h"	//�м���뷭��ΪĿ�����


int main()
{
	/* _CRT_SECURE_NO_DEPRECATE */
	/*ʹ��˵����
	���к�����Դ�����ַ���м�����ַ��������Ϣ��ַ��Ŀ������ַ
	��Ŀ������ַ���ļ�����mips���뼴��ִ��
	һ���ջ�bug���˲����κ����Σ�Ц��
	*/


	//*compiler to do list*/
//1.read the writen file's address
	printf("��������Ҫ��ȡ�ļ����ļ�·����ע��windows����Ҫ\\˫б�ܣ���\n");
	gets(read_file);
	fp_read = fopen(read_file, "r");
	if (fp_read == NULL) {
		perror("open read_file failed");
		return 0;
	}
//2.read the output files' addresses
	//inter code file:
	interPrintStart();
	//final code file:
	finalPrintStart();
	

//3.new ftable//new glosymtable//cursymtalbe = glosymtable
	ftable = newFunTable();
	glosymtable = newSymTable();
	if (ftable == NULL || glosymtable == NULL) {
		//�������ű�ʧ��
		tableErr(7);
		return 0;
	}
	cursymtable = glosymtable;
//4.start the process

	if (inter_debug) {
		printf("inter_code_debug start!\n");
		nextsym();
		isProgram();
		printf("inter_code_debug finish!\n");
		interPrintEnd();
		finalPrintProceed();
	}

//5.close all the files has been opened
	printErrorNum();
	return 0;
}

