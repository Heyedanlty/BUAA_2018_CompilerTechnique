#include "err.h"
#include "symtable.h"
int errors = 0;

void err(/*������*/int index) {
	errors++;
	printf( "line %4d :  ", line_number);
	switch (index) {
	case 1: printf( "�Ƿ��ַ�				invalid symbol\n"); break;
	case 2: printf( "�ַ����ڴ��ڷǷ��ַ�	invalid symbol in string\n"); break;
	case 3: printf( "ȱ��˫�����������ַ���	need double quatation mark to end a string\n"); break;
	case 4: printf( "�ַ������ڵ�ֵ���Ϸ�	invalid symbol of char\n"); break;
	case 5: printf( "ȱ�ٷֺ�				need semicolon \";\"\n"); break;
	case 6: printf( "ȱ�ٵȺ�				need equal mark \"=\"\n"); break;
	case 7: printf( "�����ִ���				wrong reserved symbol\n"); break;
	case 8: printf( "ȱ�����ͱ�����			need reserved symbol of type \"int\"or\"char\"\n"); break;
	case 9: printf( "ȱ���ҷ�����			need closing brackets \"]\"\n"); break;
	case 10: printf( "ȱ���Ҵ�����			need closing braces \"}\"\n"); break;
	case 11: printf( "ȱ���������			need left braces \"{\"\n"); break;
	case 12: printf( "ȱ��������			need right parentheses \")\"\n"); break;
	case 13: printf( "ȱ��������			need left parentheses \"(\"\n"); break;
	case 14: printf( "ȱ�ٱ�ʶ��			need an identifier\n"); break;
	case 15: printf( "ȱ��������			need left brackets \"[\"\n"); break;
	case 16: printf( "ȱ��ð��				need colon \":\"\n"); break;
	case 17: printf( "ȱ�ٶ���				need comma \",\"\n"); break;
	case 18: printf( "ȱ��main������		need reserved symbol \"main\"\n"); break;
	case 19: printf( "��Ҫһ������			need divisor\n"); break;
	case 20: printf( "�������				wrong symbol\n"); break;
	case 21: printf( "ȱ��main��������		need defination of main\n"); break;
	case 22: printf( "ȱ�ٵȺŻ�������		need equal mark \"=\" or left parentheses\"(\"\n"); break;
	case 23: printf( "ȱ�ٵȺŻ�������	need equal mark \"=\" or left brackets \"[\"\n"); break;
	case 24: printf( "ȱ�ٶ��Ż�������		need comma \",\" or right parentheses \")\"\n"); break;
	case 25: printf( "ȱ�ٶ��Ż�������	need comma \",\" or left brackets \"[\"\n"); break;
	case 26: printf( "ȱ���޷�������		need an unsigned integer\n"); break;
	case 27: printf( "ȱ������				need an integer\n"); break;
	case 28: printf( "ȱ���ַ�				need a char\n"); break;
	case 29: printf( "ȱ�ٳ���				need a constant value\n"); break;
	case 30: printf( "δ����ĺ���			using of a function without declaration\n"); break;
	case 31: printf( "Ӧʹ���з���ֵ����	should be a using of function with return value\n"); break;
	case 32: printf( "ʹ����δ����ı�ʶ��	using of a identifier without declaration\n"); break;
	case 33: printf( "ȱ�ٱ��ʽ			need an expression\n"); break;
	case 34: printf("��Ҫ���ͱ��ʽ			need an int expression\n"); break;
	case 35: printf("�����±�ֵԽ��			invalid value of index for array\n"); break;
	case 36: printf("��ֵ����������Ͳ�ͬ	wrong type of assignment\n"); break;
	case 37: printf("���ܸ�����ֵ������ֵ	invalid assignment to an array or constant value\n"); break;
	case 38: printf("Case��������ʽ��һ��	different type of case and switch\n"); break;
	case 39: printf("������������			wrong amount of parameters\n"); break;
	case 40: printf("�������ʹ���			wrong type of parameter\n"); break;
	case 41: printf("���붨��void main		the return value of main must be void\n"); break;
	case 42: printf("main������ַ�			too much symbols after main defination\n"); break;
	case 43: printf("���������������������Ҫ������		wrong ending of the code, maybe need right braces \"}\"\n"); getchar(); exit(0); break;
	}
	return;
}

void tableErr(/*������*/int index) {
	errors++;
	printf("line %4d :  ", line_number);
	switch (index) {
	case 1:printf("������������		can't insert: declare too much functions\n"); break;
	case 2:printf("�����ظ�����		can't insert: function having the same name has already been declared\n"); break;
	case 3:printf("��������			this function has too much parameters\n"); break;
	case 4:printf("����ͬ��			this function has declared a parameter having the same name\n"); break;
	case 5:printf("������������		this function has too much declare of symbols\n"); break;
	case 6:printf("�ظ���������		this function has declared a symbol having the same name\n"); break;
	case 7:printf("���ű��ʼ��ʧ��	error happened when initializing symbol tables\n"); break;
	}
	/*showGloSym();*/
	return;
}

void printErrorNum() {
	if (errors != 0) {
		printf("���棺���α������%d������,����ִ��mips����\n", errors);
	}
	else {
		printf("���α���ͨ�������Գ���ִ��mips����\n");
	}
}