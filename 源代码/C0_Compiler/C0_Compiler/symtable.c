#include "symtable.h"

funtable *ftable = NULL;
symtable *glosymtable = NULL,*cursymtable = NULL;


/*--------------------------------------------------
建立新的函数表
失败返回NULL
成功返回函数表指针
--------------------------------------------------*/
funtable *newFunTable() {
	funtable *ftp_tmp;
	ftp_tmp = (funtable *)malloc(sizeof(funtable));
	if (ftp_tmp == NULL) {
		return ftp_tmp;
	}
	ftp_tmp->used = 0;
	return ftp_tmp;
}

/*--------------------------------------------------
在函数表中查找函数（全局只有一个函数表）
失败返回-1
成功返回位置（0开始）
--------------------------------------------------*/
int searchFun(char *name, int namelen) {
	if (ftable->used == 0) {
		return -1;
	}
	else {
		int i, j;
		for (i = 0; i < ftable->used; i++) {
			if (namelen == ftable->fun[i].namelen) {
				for (j = 0; j < namelen; j++) {
					if (ftable->fun[i].name[j] != name[j]) {
						break;
					}
				}
				if (j == namelen) {
					return i;
				}
			}
		}
		return -1;
	}
}

/*--------------------------------------------------
向函数表中插入新函数（全局只有一个函数表）
失败返回-1
成功返回0
--------------------------------------------------*/
int insertFun(char *name, int namelen, int value) {
	if (ftable->used == MAX_FUN_NUM) {
		tableErr(1);
		return _FULL_TABLE_;//插入失败，函数表满
	}
	else if (searchFun(name, namelen) != -1) {
		tableErr(2);
		return _IN_TABLE_;//插入失败，已存在函数
	}
	else {
		ftable->fun[ftable->used].namelen = namelen;
		ftable->fun[ftable->used].value = value;
		memset(ftable->fun[ftable->used].name, 0, sizeof(ftable->fun[ftable->used].name));
		for (int i = 0; i < namelen; i++) {
			ftable->fun[ftable->used].name[i] = name[i];
		}
		ftable->fun[ftable->used].stp = (symtable *)malloc(sizeof(symtable));
		if (ftable->fun[ftable->used].stp == NULL) {
			tableErr(7);
			return -1;//建立符号表失败
		}
		ftable->fun[ftable->used].stp->numofpara = 0;
		ftable->fun[ftable->used].stp->used = 0;
		ftable->fun[ftable->used].stp->usespace = 0;

		cursymtable = ftable->fun[ftable->used].stp;
		ftable->used++;
		return 0;
	}
}

/*--------------------------------------------------
展示函数表
--------------------------------------------------*/
void showFunTable() {
	if (ftable->used == 0) {
		printf("This function table is empty!\n");
	}
	else {
		int i;
		for (i = 0; i < ftable->used; i++) {
			printf("--------------------------------------------------\n");
			printf("fun%d has these attributes\n", i);
			printf("name of this function:	%s\n", ftable->fun[i].name);
			printf("return value type:		%s\n", ftable->fun[i].value == INT ? "int" : ftable->fun[i].value == CHAR ? "char" : "void");
			printf("number of parameter:	%d\n", ftable->fun[i].stp->numofpara);
			printf("size of function:		%d\n", ftable->fun[i].stp->usespace);
			printf("--------------------------------------------------\n");
		}
	}
	return;
}

/*--------------------------------------------------
建立新的符号表
失败返回NULL
成功返回符号表指针
--------------------------------------------------*/
symtable *newSymTable() {
	symtable *stp_tmp;
	stp_tmp = (symtable *)malloc(sizeof(symtable));
	if (stp_tmp == NULL) {
		return stp_tmp;
	}
	stp_tmp->numofpara = 0;
	stp_tmp->used = 0;
	stp_tmp->usespace = 0;
	return stp_tmp;
}

/*--------------------------------------------------
在当前环境中寻找是否有相同符号
没有返回-1
有返回位置值（0开始）
--------------------------------------------------*/
int searchSym(char *name, int namelen) {
	if (cursymtable->used == 0) {
		return -1;//没有这个符号
	}
	else {
		int i, j;
		for (i = 0; i < cursymtable->used; i++) {
			if (namelen != cursymtable->sym[i].namelen) {
				continue;
			}
			for (j = 0; j < namelen; j++) {
				if (cursymtable->sym[i].name[j] != name[j]) {
					break;
				}
			}
			if (j == namelen) {
				return i;
			}
		}
		return -1;
	}
}
/*--------------------------------------------------
在全局环境中寻找是否有相同符号
没有返回-1
有返回位置值（0开始）
--------------------------------------------------*/
int searchGlobalSym(char *name, int namelen) {
	if (glosymtable->used == 0) {
		return -1;//没有这个符号
	}
	else {
		int i, j;
		for (i = 0; i < glosymtable->used; i++) {
			if (namelen != glosymtable->sym[i].namelen) {
				continue;
			}
			for (j = 0; j < namelen; j++) {
				if (glosymtable->sym[i].name[j] != name[j]) {
					break;
				}
			}
			if (j == namelen) {
				return i;
			}
		}
		return -1;
	}
}

/*--------------------------------------------------
在当前环境中创建新参数
失败返回	_TOO_MUC_PAR_
			_FULL_TABLE_
			_ARL_HAS_PAR_
成功返回0
--------------------------------------------------*/
int addPara(char *paraname, int paralen, int paratype, int definite) 
{//给函数添加参数，其实函数就是现在的环境
	if (cursymtable->numofpara == MAX_PAR_NUM) {
		tableErr(3);
		return _TOO_MUC_PAR_;//参数超过数量限制
	}
	else if (cursymtable->used == MAX_SYM_NUM) {
		tableErr(5);
		return _FULL_TABLE_;//符号表满（理论上应该不会进入这个分支）
	}
	else if (searchSym(paraname,paralen)!=-1) {
		tableErr(4);
		return _ALR_HAS_PAR_;//该函数有同名的参数
	}
	else {
		int used_tmp = cursymtable->used;
		cursymtable->numofpara++;
		memset(cursymtable->sym[used_tmp].name, 0, sizeof(cursymtable->sym[used_tmp].name));
		for (int i = 0; i < paralen; i++) {
			cursymtable->sym[used_tmp].name[i] = paraname[i];
		}
		cursymtable->sym[used_tmp].namelen = paralen;
		cursymtable->sym[used_tmp].kind = VARIABLE;
		cursymtable->sym[used_tmp].type = paratype;
		cursymtable->sym[used_tmp].array = NOTARR;
		cursymtable->sym[used_tmp].upbound = 0;
		cursymtable->sym[used_tmp].offset = cursymtable->usespace;
		cursymtable->sym[used_tmp].definite = definite;
		if (paratype == INT) {
			cursymtable->usespace += 4;
		}
		else {//paratype ==CHAR
			cursymtable->usespace += 4;
		}
		cursymtable->used++;
		return 0;
	}
}

/*--------------------------------------------------
在当前环境中创建新符号
失败返回	_FULL_TABLE_
			_ALR_HAS_PAR_
成功返回0
--------------------------------------------------*/
int addSym(char *symname, int symlen, int symkind, int symtype, int symarray, int symupbound,int symvalue, int definite) 
{//给函数添加符号,其实函数就是现在的环境
	if (cursymtable->used == MAX_SYM_NUM) {
		tableErr(5);
		return _FULL_TABLE_;//符号表满
	}
	else if (searchSym(symname, symlen) != -1) {
		tableErr(6);
		return _ALR_HAS_PAR_;//该函数有同名的参数或符号
	}
	else {
		int used_tmp = cursymtable->used;

		memset(cursymtable->sym[used_tmp].name, 0, sizeof(cursymtable->sym[used_tmp].name));
		for (int i = 0; i < symlen; i++) {
			cursymtable->sym[used_tmp].name[i] = symname[i];
		}
		cursymtable->sym[used_tmp].namelen = symlen;
		cursymtable->sym[used_tmp].kind = symkind;
		cursymtable->sym[used_tmp].type = symtype;
		cursymtable->sym[used_tmp].array = symarray;
		cursymtable->sym[used_tmp].upbound = symupbound;
		cursymtable->sym[used_tmp].value = symvalue;
		cursymtable->sym[used_tmp].offset = cursymtable->usespace;
		cursymtable->sym[used_tmp].definite = definite;
		if (symarray) {
			if (symtype == INT) {
				cursymtable->usespace += 4 * symupbound;
			}
			else {//symtype ==CHAR
				cursymtable->usespace += (symupbound / 4 + 1) * 4;
			}
		}
		else {
			if (symtype == INT) {
				cursymtable->usespace += 4;
			}
			else {//symtype ==CHAR
				cursymtable->usespace += 4;
			}
		}

		cursymtable->used++;
		return 0;
	}
}

void showCurSym() {
	if (cursymtable->used == 0) {
		printf("cur sym table is empty!\n");
		return;
	}
	else {
		for (int i = 0; i < cursymtable->used; i++) {
			printf("%s %d\n",cursymtable->sym[i].name,cursymtable->sym[i].definite);
		}
	}
}
void showGloSym() {
	printf("showing!\n");
	if (glosymtable->used == 0) {
		printf("glo sym table is empty!\n");
		return;
	}
	else {
		for (int i = 0; i < glosymtable->used; i++) {
			printf("%s %d %d\n", glosymtable->sym[i].name, glosymtable->sym[i].definite, glosymtable->sym[i].array);
		}
	}
}