#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "macrodef.h"
#include "err.h"		//错误处理
#include "nextsym.h"	//词法分析head
#include "gramma.h"		//语法分析head
#include "symtable.h"	//符号表head
#include "translate.h"	//中间代码翻译为目标代码


int main()
{
	/* _CRT_SECURE_NO_DEPRECATE */
	/*使用说明：
	运行后输入源代码地址、中间代码地址、错误信息地址、目标代码地址
	从目标代码地址的文件拷出mips代码即可执行
	一切烧机bug本人不负任何责任（笑）
	*/


	//*compiler to do list*/
//1.read the writen file's address
	printf("请输入需要读取文件的文件路径（注：windows下需要\\双斜杠）：\n");
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
		//创建符号表失败
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

