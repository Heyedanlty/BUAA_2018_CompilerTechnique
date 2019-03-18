#include "symtable.h"

funtable *ftable = NULL;
symtable *glosymtable = NULL,*cursymtable = NULL;


/*--------------------------------------------------
�����µĺ�����
ʧ�ܷ���NULL
�ɹ����غ�����ָ��
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
�ں������в��Һ�����ȫ��ֻ��һ��������
ʧ�ܷ���-1
�ɹ�����λ�ã�0��ʼ��
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
�������в����º�����ȫ��ֻ��һ��������
ʧ�ܷ���-1
�ɹ�����0
--------------------------------------------------*/
int insertFun(char *name, int namelen, int value) {
	if (ftable->used == MAX_FUN_NUM) {
		tableErr(1);
		return _FULL_TABLE_;//����ʧ�ܣ���������
	}
	else if (searchFun(name, namelen) != -1) {
		tableErr(2);
		return _IN_TABLE_;//����ʧ�ܣ��Ѵ��ں���
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
			return -1;//�������ű�ʧ��
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
չʾ������
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
�����µķ��ű�
ʧ�ܷ���NULL
�ɹ����ط��ű�ָ��
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
�ڵ�ǰ������Ѱ���Ƿ�����ͬ����
û�з���-1
�з���λ��ֵ��0��ʼ��
--------------------------------------------------*/
int searchSym(char *name, int namelen) {
	if (cursymtable->used == 0) {
		return -1;//û���������
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
��ȫ�ֻ�����Ѱ���Ƿ�����ͬ����
û�з���-1
�з���λ��ֵ��0��ʼ��
--------------------------------------------------*/
int searchGlobalSym(char *name, int namelen) {
	if (glosymtable->used == 0) {
		return -1;//û���������
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
�ڵ�ǰ�����д����²���
ʧ�ܷ���	_TOO_MUC_PAR_
			_FULL_TABLE_
			_ARL_HAS_PAR_
�ɹ�����0
--------------------------------------------------*/
int addPara(char *paraname, int paralen, int paratype, int definite) 
{//��������Ӳ�������ʵ�����������ڵĻ���
	if (cursymtable->numofpara == MAX_PAR_NUM) {
		tableErr(3);
		return _TOO_MUC_PAR_;//����������������
	}
	else if (cursymtable->used == MAX_SYM_NUM) {
		tableErr(5);
		return _FULL_TABLE_;//���ű�����������Ӧ�ò�����������֧��
	}
	else if (searchSym(paraname,paralen)!=-1) {
		tableErr(4);
		return _ALR_HAS_PAR_;//�ú�����ͬ���Ĳ���
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
�ڵ�ǰ�����д����·���
ʧ�ܷ���	_FULL_TABLE_
			_ALR_HAS_PAR_
�ɹ�����0
--------------------------------------------------*/
int addSym(char *symname, int symlen, int symkind, int symtype, int symarray, int symupbound,int symvalue, int definite) 
{//��������ӷ���,��ʵ�����������ڵĻ���
	if (cursymtable->used == MAX_SYM_NUM) {
		tableErr(5);
		return _FULL_TABLE_;//���ű���
	}
	else if (searchSym(symname, symlen) != -1) {
		tableErr(6);
		return _ALR_HAS_PAR_;//�ú�����ͬ���Ĳ��������
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