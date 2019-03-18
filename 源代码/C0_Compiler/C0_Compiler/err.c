#include "err.h"
#include "symtable.h"
int errors = 0;

void err(/*错误编号*/int index) {
	errors++;
	printf( "line %4d :  ", line_number);
	switch (index) {
	case 1: printf( "非法字符				invalid symbol\n"); break;
	case 2: printf( "字符串内存在非法字符	invalid symbol in string\n"); break;
	case 3: printf( "缺少双引号来结束字符串	need double quatation mark to end a string\n"); break;
	case 4: printf( "字符类型内的值不合法	invalid symbol of char\n"); break;
	case 5: printf( "缺少分号				need semicolon \";\"\n"); break;
	case 6: printf( "缺少等号				need equal mark \"=\"\n"); break;
	case 7: printf( "保留字错误				wrong reserved symbol\n"); break;
	case 8: printf( "缺少类型保留字			need reserved symbol of type \"int\"or\"char\"\n"); break;
	case 9: printf( "缺少右方括号			need closing brackets \"]\"\n"); break;
	case 10: printf( "缺少右大括号			need closing braces \"}\"\n"); break;
	case 11: printf( "缺少左大括号			need left braces \"{\"\n"); break;
	case 12: printf( "缺少右括号			need right parentheses \")\"\n"); break;
	case 13: printf( "缺少左括号			need left parentheses \"(\"\n"); break;
	case 14: printf( "缺少标识符			need an identifier\n"); break;
	case 15: printf( "缺少左方括号			need left brackets \"[\"\n"); break;
	case 16: printf( "缺少冒号				need colon \":\"\n"); break;
	case 17: printf( "缺少逗号				need comma \",\"\n"); break;
	case 18: printf( "缺少main保留字		need reserved symbol \"main\"\n"); break;
	case 19: printf( "需要一个因子			need divisor\n"); break;
	case 20: printf( "错误符号				wrong symbol\n"); break;
	case 21: printf( "缺少main函数定义		need defination of main\n"); break;
	case 22: printf( "缺少等号或左括号		need equal mark \"=\" or left parentheses\"(\"\n"); break;
	case 23: printf( "缺少等号或左方括号	need equal mark \"=\" or left brackets \"[\"\n"); break;
	case 24: printf( "缺少逗号或右括号		need comma \",\" or right parentheses \")\"\n"); break;
	case 25: printf( "缺少逗号或左方括号	need comma \",\" or left brackets \"[\"\n"); break;
	case 26: printf( "缺少无符号整数		need an unsigned integer\n"); break;
	case 27: printf( "缺少整数				need an integer\n"); break;
	case 28: printf( "缺少字符				need a char\n"); break;
	case 29: printf( "缺少常量				need a constant value\n"); break;
	case 30: printf( "未定义的函数			using of a function without declaration\n"); break;
	case 31: printf( "应使用有返回值函数	should be a using of function with return value\n"); break;
	case 32: printf( "使用了未定义的标识符	using of a identifier without declaration\n"); break;
	case 33: printf( "缺少表达式			need an expression\n"); break;
	case 34: printf("需要整型表达式			need an int expression\n"); break;
	case 35: printf("数组下标值越界			invalid value of index for array\n"); break;
	case 36: printf("赋值语句左右类型不同	wrong type of assignment\n"); break;
	case 37: printf("不能给数组值或常量赋值	invalid assignment to an array or constant value\n"); break;
	case 38: printf("Case类型与表达式不一致	different type of case and switch\n"); break;
	case 39: printf("参数数量错误			wrong amount of parameters\n"); break;
	case 40: printf("参数类型错误			wrong type of parameter\n"); break;
	case 41: printf("必须定义void main		the return value of main must be void\n"); break;
	case 42: printf("main后多余字符			too much symbols after main defination\n"); break;
	case 43: printf("代码非正常结束，可能需要大括号		wrong ending of the code, maybe need right braces \"}\"\n"); getchar(); exit(0); break;
	}
	return;
}

void tableErr(/*错误编号*/int index) {
	errors++;
	printf("line %4d :  ", line_number);
	switch (index) {
	case 1:printf("函数声明过多		can't insert: declare too much functions\n"); break;
	case 2:printf("函数重复声明		can't insert: function having the same name has already been declared\n"); break;
	case 3:printf("参数过多			this function has too much parameters\n"); break;
	case 4:printf("参数同名			this function has declared a parameter having the same name\n"); break;
	case 5:printf("符号声明过多		this function has too much declare of symbols\n"); break;
	case 6:printf("重复声明符号		this function has declared a symbol having the same name\n"); break;
	case 7:printf("符号表初始化失败	error happened when initializing symbol tables\n"); break;
	}
	/*showGloSym();*/
	return;
}

void printErrorNum() {
	if (errors != 0) {
		printf("警告：本次编译产生%d个错误,请勿执行mips代码\n", errors);
	}
	else {
		printf("本次编译通过，可以尝试执行mips代码\n");
	}
}