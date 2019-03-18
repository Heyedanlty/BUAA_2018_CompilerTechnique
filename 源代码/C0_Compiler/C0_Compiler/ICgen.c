#include "ICgen.h"


char inter_file[MAX_FILE_LEN];
char inter_file2[MAX_FILE_LEN];
FILE *fp_inter;
FILE *fp_inter2;
int inter_debug = 1;

int while_counter = 1;
int if_counter = 1;
int switch_counter = 1;
int case_counter = 1;

int reg_pool[10] = { 0 };
void resetRegPool() {
	for (int i = 0; i < 10; i++) {
		reg_pool[i] = 0;
	}
}
int newRegCounter() {
	for (int i = 0; i < 10; i++) {
		if (reg_pool[i] == 0) {
			reg_pool[i] = 1;
			return i;
		}
	}
	return -1;
}
void releaseRegCounter(int i) {
	reg_pool[i] = 0;
}
void saveTmpRegisters() {
	for (int i = 0; i < 10; i++) {
		if (reg_pool[i] == 1) {
			fprintf(fp_inter, "SW t%d %d(sp)\n",i,i*4);
		}
	}
}
void getTmpRegisters() {
	for (int i = 0; i < 10; i++) {
		if (reg_pool[i] == 1) {
			fprintf(fp_inter, "LW t%d = %d(sp)\n", i, i * 4);
		}
	}
}


void interPrintStart() {
	printf("请输入输出中间代码的文件路径（注：windows下需要\\双斜杠）：\n");
	gets(inter_file);
	printf("请输入输出中间代码(优化后）的文件路径（注：windows下需要\\双斜杠）：\n");
	gets(inter_file2);
	fp_inter = fopen(inter_file, "w");
	if (fp_inter == NULL) {
		perror("open intermediate code file failed");
	}
	fp_int = fp_inter;
	return;
}
void interPrintEnd() {
	if (fclose(fp_inter) == EOF) {
		perror("close intermediate code file failed");
	}
	intercpy();
	return;
}

void intercpy() {
	char *buff;
	int ret;
	fp_inter = fopen(inter_file, "r");
	fp_inter2 = fopen(inter_file2, "w");
	if (fp_inter == NULL || fp_inter2 == NULL) {
		perror("open failed!\n");
		return;
	}
	buff = (char *)malloc(BUFFSIZE);
	if (buff == NULL) {
		printf("buff filed\n");
		return;
	}
	while (1) {
		ret = fread(buff, 1, BUFFSIZE, fp_inter);
		if (ret != BUFFSIZE) {
			fwrite(buff, ret, 1, fp_inter2);
		}
		else {
			fwrite(buff, BUFFSIZE, 1, fp_inter2);
		}
		if (feof(fp_inter)) {
			break;
		}
	}
	fclose(fp_inter);
	fclose(fp_inter2);
	free(buff);
	return;
}




void resetCaseCounter() {
	case_counter = 1;
}
void interPrintGetCase(int *case_index) {
	*case_index = case_counter++;
}

//void interPrintString(char *str) {
//	fprintf(fp_inter, "%s", str);
//}
//void interPrintLabel(int i) {
//	fprintf(fp_inter, "LABEL label_%d:\n", i);
//}
/*const defination instruction global and function*/
void interPrintGLOCST(char *name, int namelen, int type, int value) {
	fprintf(fp_inter,"GLOCST ");
	for (int i = 0; i < namelen; i++) {
		fprintf(fp_inter,"%c", name[i]);
	}
	fprintf(fp_inter," 4\n");
	fprintf(fp_inter,"GLOCSTASS\n");
	fprintf(fp_inter, "LI t1 = %d\n",value);
	if (type == INT) {
		fprintf(fp_inter, "SW t1 ");
	}
	else {
		fprintf(fp_inter, "SB t1 ");
	}
	for (int i = 0; i < namelen; i++) {
		fprintf(fp_inter, "%c", name[i]);
	}
	fprintf(fp_inter, "\n");
	return;
	/*fprintf(fp_inter,".data\n");
	for (int i = 0; i < namelen; i++) {
		fprintf(fp_inter,"%c", name[i]);
	}
	fprintf(fp_inter,":.space ");
	if (type == INT) {
		fprintf(fp_inter, "4\n");
	}
	else {
		fprintf(fp_inter, "1\n");
	}
	fprintf(fp_inter,".text\n");
	fprintf(fp_inter, "li $t0,%d\n",value);
	if (type == INT) {
		fprintf(fp_inter, "sw $t0,");
	}
	else {
		fprintf(fp_inter, "sb $t0,");
	}
	for (int i = 0; i < namelen; i++) {
		fprintf(fp_inter, "%c", name[i]);
	}
	fprintf(fp_inter, "\n");*/
}
void interPrintFUNCST(int type, int value, int offset) {
	fprintf(fp_inter, "LI t1 = %d\n",value);
	if (type == INT) {
		fprintf(fp_inter, "SW t1 %d(sp)\n", offset+40);
	}
	else {
		fprintf(fp_inter, "SB t1 %d(sp)\n", offset+40);
	}
	return;
}
/*global variation def*/
void interPrintGLOVAR() {
	fprintf(fp_inter, "GLOVARSTART\n");
	int i;
	for (i = 0; i < glosymtable->used; i++) {
		if (glosymtable->sym[i].kind == VARIABLE) {
			fprintf(fp_inter, "GLOVAR %s ", glosymtable->sym[i].name);
			if (glosymtable->sym[i].type == INT) {
				if (glosymtable->sym[i].array == ARR) {
					fprintf(fp_inter,"%d\n", 4 * (glosymtable->sym[i].upbound));
				}
				else {
					fprintf(fp_inter, "%d\n", 4);
				}
			}
			else {
				if (glosymtable->sym[i].array == ARR) {
					fprintf(fp_inter, "%d\n", 4*((glosymtable->sym[i].upbound)/4+1));
				}
				else {
					fprintf(fp_inter, "%d\n", 4);
				}
			}
		}
	}
	fprintf(fp_inter, "GLOVAREND\n");
	//解析时需要增加j至main的部分
}
/*function defination*/
void interPrintFUNDEF(char *funname, int funnamelen) {
	fprintf(fp_inter, "LABEL FUN_");
	for (int i = 0; i < funnamelen; i++) {
		fprintf(fp_inter, "%c", funname[i]);
	}
	fprintf(fp_inter, ":\n");
}
void interPrintFUNEND() {
	fprintf(fp_inter, "LABEL FUN_END:\n");
}
/*expression instruction*/
void interPrintExpNDND(int para1, int para2, int addflag) {
	if (addflag == 1) {
		fprintf(fp_inter, "ADD t%d = t%d + t%d\n", para1, para1, para2);
	}
	else {
		fprintf(fp_inter, "SUB t%d = t%d - t%d\n", para1, para1, para2);
	}
}
void interPrintExpDND(int para1, int const2, int addflag, int whoisconst) {
	if (addflag == 1) {
		fprintf(fp_inter, "ADDI t%d = t%d + %d\n", para1, para1, const2);
	}
	else {
		if (whoisconst == 2) {
			fprintf(fp_inter, "SUBI t%d = t%d - %d\n", para1, para1, const2);
		}
		else {
			int tmp;
			tmp = newRegCounter();
			fprintf(fp_inter, "LI t%d = %d\n", tmp, const2);
			fprintf(fp_inter, "SUB t%d = t%d - t%d\n", para1, tmp, para1);
			releaseRegCounter(tmp);
		}
	}
}
/*term instruction*/
void interPrintTrmNDND(int para1, int para2, int mulflag) {
	if (mulflag == 1) {
		fprintf(fp_inter, "MUL t%d = t%d * t%d\n", para1, para1, para2);
	}
	else {
			fprintf(fp_inter, "DIV t%d = t%d / t%d\n", para1, para1, para2);
	}
}
void interPrintTrmDND(int para1, int para2, int mulflag, int whoisconst) {
	if (mulflag == 1) {
		fprintf(fp_inter, "MULI t%d = t%d * %d\n", para1, para1, para2);
	}
	else {
		if (whoisconst == 2) {
			fprintf(fp_inter, "DIVI t%d = t%d / %d\n", para1, para1, para2);
		}
		else {
			int tmp;
			tmp = newRegCounter();
			fprintf(fp_inter, "LI t%d = %d\n", tmp, para2);
			fprintf(fp_inter, "DIV t%d = t%d / t%d\n", para1, tmp, para1);
			releaseRegCounter(tmp);
		}
	}
}
/*use of function return value*/
void interPrintRTRVLE(int counter) {
	fprintf(fp_inter, "MOVE t%d = v0\n", counter);
}
/*array access instruction*/
void interPrintGLOARRACC1(int counter, char *name, int namelen, int type, int offset) {
	if (type == INT) {
		fprintf(fp_inter, "LW ");
	}
	else {
		fprintf(fp_inter, "LB ");
	}
	fprintf(fp_inter, "t%d = ", counter);
	for (int i = 0; i < namelen; i++) {
		fprintf(fp_inter, "%c", name[i]);
	}
	fprintf(fp_inter, " + %d\n", offset);
}
void interPrintCURARRACC1(int counter, int type, int offset) {
	if (type == INT) {
		fprintf(fp_inter, "LW ");
	}
	else {
		fprintf(fp_inter, "LB ");
	}
	fprintf(fp_inter, "t%d = %d(sp)\n", counter, offset+40);
}
void interPrintGLOARRACC2(int counter, char *name, int namelen, int type, int counter2) {
	if (type == INT) {
		fprintf(fp_inter, "MULI t%d = t%d * 4\n", counter2, counter2);
		fprintf(fp_inter, "LW ");
	}
	else {
		fprintf(fp_inter, "LB ");
	}
	fprintf(fp_inter, "t%d = ", counter);
	for (int i = 0; i < namelen; i++) {
		fprintf(fp_inter, "%c", name[i]);
	}
	fprintf(fp_inter, "(t%d)\n", counter2);
}
void interPrintCURARRACC2(int counter, int type, int counter2, int offsetofarray) {
	if (type == INT) {
		fprintf(fp_inter, "MULI t%d = t%d * 4\n",counter2,counter2);
	}
	fprintf(fp_inter, "ADD t%d = t%d + sp\n",counter2,counter2);
	/*fprintf(fp_inter, "ADDI t%d = t%d + %d\n", counter2, counter2, offsetofarray);*/
	if (type == INT) {
		fprintf(fp_inter, "LW ");
	}
	else {
		fprintf(fp_inter, "LB ");
	}
	fprintf(fp_inter, "t%d = %d(t%d)\n", counter, offsetofarray+40, counter2);
}
void interPrintGLOVARACC(int counter, char *name, int namelen, int type) {/*global var access*/
	if (type == INT) {
		fprintf(fp_inter, "LW ");
	}
	else {
		fprintf(fp_inter, "LB ");
	}
	fprintf(fp_inter, "t%d = ", counter);
	for (int i = 0; i < namelen; i++) {
		fprintf(fp_inter, "%c", name[i]);
	}
	fprintf(fp_inter, "\n");
}
void interPrintCURVARACC(int counter, int type, int offset) {/*current var access*/
	if (type == INT) {
		fprintf(fp_inter, "LW ");
	}
	else {
		fprintf(fp_inter, "LB ");
	}
	fprintf(fp_inter, "t%d = %d(sp)\n", counter, offset+40);
}
/*return instruction*/
void interPrintStoreReturnValue(int v_const, int v_value, int v_counter) {
	if (v_const) {
		fprintf(fp_inter, "LI v0 = %d\n", v_value);
	}
	else {
		fprintf(fp_inter, "MOVE v0 = t%d\n", v_counter);
	}
}
void interPrintRETURN() {
	int offset = cursymtable->usespace;
	fprintf(fp_inter, "LW ra = %d(sp)\n",offset+44);
	fprintf(fp_inter, "LW sp = %d(sp)\n", offset+40);
	fprintf(fp_inter, "JR ra\n");
}
/*printf instruction*/
void interPrintPRINTFSTR(char *str, int strlen) {
	fprintf(fp_inter, "PRTSTR ");
	for (int i = 0; i < strlen; i++) {
		fprintf(fp_inter, "%c", str[i]);
	}
	fprintf(fp_inter, "\n");
}
void interPrintPRINTFEXP(int exp_type, int exp_const, int exp_value, int exp_counter) {
	if (exp_const) {
		fprintf(fp_inter, "LI a0 = %d\n", exp_value);
		if (exp_type == INT) {
			fprintf(fp_inter, "LI v0 = 1\n");
		}
		else {
			fprintf(fp_inter, "LI v0 = 11\n");
		}
		fprintf(fp_inter, "SYSCALL\n");
	}
	else {
		fprintf(fp_inter, "MOVE a0 = t%d\n", exp_counter);
		if (exp_type == INT) {
			fprintf(fp_inter, "LI v0 = 1\n");
		}
		else {
			fprintf(fp_inter, "LI v0 = 11\n");
		}
		fprintf(fp_inter, "SYSCALL\n");
		releaseRegCounter(exp_counter);
	}
}
void interPrintPRINTFENTER() {
	fprintf(fp_inter, "LI a0 = 10\n");
	fprintf(fp_inter, "LI v0 = 11\n");
	fprintf(fp_inter, "SYSCALL\n");
}
void interPrintPRINTFSPACE() {
	fprintf(fp_inter, "LI a0 = 32\n");
	fprintf(fp_inter, "LI v0 = 11\n");
	fprintf(fp_inter, "SYSCALL\n");
}
/*scanf instruction*/
void interPrintSCANFCUR(int identype, int offset) {
	if (identype == INT) {
		fprintf(fp_inter, "LI v0 = 5\n");
		fprintf(fp_inter, "SYSCALL\n");
		fprintf(fp_inter, "SW v0 %d (sp)\n", offset+40);
	}
	else {
		fprintf(fp_inter, "LI v0 = 12\n");
		fprintf(fp_inter, "SYSCALL\n");
		fprintf(fp_inter, "SB v0 %d (sp)\n", offset+40);
	}
}
void interPrintSCANFGLO(char *idenname, int idennamelen, int identype) {
	if (identype == INT) {
		fprintf(fp_inter, "LI v0 = 5\n");
		fprintf(fp_inter, "SYSCALL\n");
		fprintf(fp_inter, "SW a0 ");
		for (int i = 0; i < idennamelen; i++) {
			fprintf(fp_inter, "%c", idenname[i]);
		}
		fprintf(fp_inter, "\n");
	}
	else {
		fprintf(fp_inter, "LI v0 = 12\n");
		fprintf(fp_inter, "SYSCALL\n");
		fprintf(fp_inter, "SB a0 ");
		for (int i = 0; i < idennamelen; i++) {
			fprintf(fp_inter, "%c", idenname[i]);
		}
		fprintf(fp_inter, "\n");
	}
}
/*assign instruction*/
void interPrintASSGLOCST(char *idenname, int idennamelen, int identype, int idenvalue) {
	int reg_tmp = newRegCounter();
	fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,idenvalue);
	if (identype == INT) {
		fprintf(fp_inter, "SW t%d ", reg_tmp);
		for (int i = 0; i < idennamelen; i++) {
			fprintf(fp_inter, "%c", idenname[i]);
		}
		fprintf(fp_inter, "\n");
	}
	else {
		fprintf(fp_inter, "SB t%d ", reg_tmp);
		for (int i = 0; i < idennamelen; i++) {
			fprintf(fp_inter, "%c", idenname[i]);
		}
		fprintf(fp_inter, "\n");
	}
	releaseRegCounter(reg_tmp);
}
void interPrintASSGLOVAR(char *idenname, int idennamelen, int identype, int idencounter) {
	if (identype == INT) {
		fprintf(fp_inter, "SW t%d ", idencounter);
		for (int i = 0; i < idennamelen; i++) {
			fprintf(fp_inter, "%c", idenname[i]);
		}
		fprintf(fp_inter, "\n");
	}
	else {
		fprintf(fp_inter, "SB t%d ", idencounter);
		for (int i = 0; i < idennamelen; i++) {
			fprintf(fp_inter, "%c", idenname[i]);
		}
		fprintf(fp_inter, "\n");
	}
	releaseRegCounter(idencounter);
}
void interPrintASSCURCST(int identype, int idenoffset, int idenvalue) {
	int reg_tmp = newRegCounter();
	fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,idenvalue);
	if (identype == INT) {
		fprintf(fp_inter, "SW t%d %d(sp)\n", reg_tmp,idenoffset+40);
	}
	else {
		fprintf(fp_inter, "SB t%d %d(sp)\n", reg_tmp,idenoffset+40);
	}
	releaseRegCounter(reg_tmp);
}
void interPrintASSCURVAR(int identype, int idenoffset, int idencounter) {
	if (identype == INT) {
		fprintf(fp_inter, "SW t%d %d(sp)\n", idencounter, idenoffset+40);
	}
	else {
		fprintf(fp_inter, "SB t%d %d(sp)\n", idencounter, idenoffset+40);
	}
	releaseRegCounter(idencounter);
}
void interPrintASSARR(int global_flag, char *idenname, int idennamelen, int identype, int idenoffset,
	int leftconst, int leftvalue, int leftcounter,
	int idenconst, int idenvalue, int idencounter)
{
	int reg_tmp = newRegCounter();
	if (global_flag) {
		if (leftconst) {
			int offset = leftvalue * (identype == INT ? 4 : 1);
			if (identype == INT) {
				if (idenconst) {
					fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,idenvalue);
					fprintf(fp_inter, "SW t%d ",reg_tmp);
					for (int i = 0; i < idennamelen; i++) {
						fprintf(fp_inter, "%c", idenname[i]);
					}
					fprintf(fp_inter, "+%d\n",offset);
				}
				else {
					fprintf(fp_inter, "SW t%d ", idencounter);
					for (int i = 0; i < idennamelen; i++) {
						fprintf(fp_inter, "%c", idenname[i]);
					}
					fprintf(fp_inter, "+%d\n",offset);
				}
			}
			else {
				if (idenconst) {
					fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,idenvalue);
					fprintf(fp_inter, "SB t%d ",reg_tmp);
					for (int i = 0; i < idennamelen; i++) {
						fprintf(fp_inter, "%c", idenname[i]);
					}
					fprintf(fp_inter, "+%d\n",offset);
				}
				else {
					fprintf(fp_inter, "SB t%d ", idencounter);
					for (int i = 0; i < idennamelen; i++) {
						fprintf(fp_inter, "%c", idenname[i]);
					}
					fprintf(fp_inter, "+%d\n",offset);
				}
			}
		}
		else {
			if (identype == INT) {
				fprintf(fp_inter, "MULI t%d = t%d * 4\n", leftcounter, leftcounter);
				fprintf(fp_inter, "SW t%d ", idencounter);
				for (int i = 0; i < idennamelen; i++) {
					fprintf(fp_inter, "%c", idenname[i]);
				}
				fprintf(fp_inter, "(t%d)\n", leftcounter);
			}
			else {
				fprintf(fp_inter, "SW t%d ", idencounter);
				for (int i = 0; i < idennamelen; i++) {
					fprintf(fp_inter, "%c", idenname[i]);
				}
				fprintf(fp_inter, "(t%d)\n", leftcounter);
			}
		}
	}
	else {
		if (leftconst) {
			int offset = leftvalue * (identype == INT ? 4 : 1) + idenoffset+40;
			if (identype == INT) {
				if (idenconst) {
					fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,idenvalue);
					fprintf(fp_inter, "SW t%d ",reg_tmp);
					fprintf(fp_inter, "%d(sp)\n", offset);
				}
				else {
					fprintf(fp_inter, "SW t%d ", idencounter);
					fprintf(fp_inter, "%d(sp)\n", offset);
				}
			}
			else {
				if (idenconst) {
					fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,idenvalue);
					fprintf(fp_inter, "SB t%d ",reg_tmp);
					fprintf(fp_inter, "%d(sp)\n", offset);
				}
				else {
					fprintf(fp_inter, "SB t%d ", idencounter);
					fprintf(fp_inter, "%d(sp)\n", offset);
				}
			}
		}
		else {
			if (identype == INT) {
				if (idenconst) {
					fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,idenvalue);
					fprintf(fp_inter, "MULI t%d = t%d * 4\n", leftcounter, leftcounter);
					fprintf(fp_inter, "ADD t%d = t%d + sp\n", leftcounter, leftcounter);
					fprintf(fp_inter, "SW t%d %d(t%d)\n",reg_tmp, idenoffset+40, leftcounter);
				}
				else {
					fprintf(fp_inter, "MULI t%d = t%d * 4\n", leftcounter, leftcounter);
					fprintf(fp_inter, "ADD t%d = t%d + sp\n", leftcounter, leftcounter);
					fprintf(fp_inter, "SW t%d %d(t%d)\n", idencounter, idenoffset+40, leftcounter);
				}

			}
			else {
				if (idenconst) {
					fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,idenvalue);
					fprintf(fp_inter, "ADD t%d = t%d + sp\n", leftcounter, leftcounter);
					fprintf(fp_inter, "SB t%d %d(t%d)\n",reg_tmp,idenoffset+40, leftcounter);
				}
				else {
					fprintf(fp_inter, "ADD t%d = t%d + sp\n", leftcounter, leftcounter);
					fprintf(fp_inter, "SB t%d %d(t%d)\n", idencounter, idenoffset+40, leftcounter);
				}
			}
		}
	}
	releaseRegCounter(reg_tmp);
}
/*while instruction*/
void interPrintWhileStart(int *while_index) {
	*while_index = while_counter++;
	fprintf(fp_inter, "LABEL WHILE_%d_START:\n", *while_index);
}
void interPrintBackWhile(int while_index) {
	fprintf(fp_inter, "J WHILE_%d_START\n", while_index);
}
void interPrintWhileEnd(int while_index) {
	fprintf(fp_inter, "LABEL WHILE_%d_END:\n", while_index);
}
/*if instruction*/
void interPrintIfStart(int *if_index) {
	*if_index = if_counter++;
	fprintf(fp_inter, "LABEL IF_%d_START:\n", *if_index);
}
void interPrintIfEnd(int if_index){
	fprintf(fp_inter, "LABEL IF_%d_END:\n", if_index);
}
/*condition instruction*/
void interPrintJudge1(int judgetype, int judge_index,
	int exp1_const, int exp1_value, int exp1_counter)
{
	int reg_tmp = newRegCounter();
	if (exp1_const) {
		fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,exp1_value);
		if (judgetype == WHILE) {
			fprintf(fp_inter, "BEQZ t%d WHILE_%d_END\n", reg_tmp,judge_index);
		}
		else {
			fprintf(fp_inter, "BEQZ t%d IF_%d_END\n", reg_tmp,judge_index);
		}
	}
	else {
		if (judgetype == WHILE) {
			fprintf(fp_inter, "BEQZ t%d WHILE_%d_END\n", exp1_counter, judge_index);
		}
		else{
			fprintf(fp_inter, "BEQZ t%d IF_%d_END\n", exp1_counter, judge_index);
		}
	}
	if (!exp1_const) {
		releaseRegCounter(exp1_counter);
	}
	releaseRegCounter(reg_tmp);
}
void interPrintJudge2(int judgetype, int judge_index, int operatorType,
	int exp1_const, int exp1_value, int exp1_counter,
	int exp2_const, int exp2_value, int exp2_counter)
{
	int reg_tmp = newRegCounter();
	if (judgetype == WHILE) {
		switch (operatorType) {
		case 0/* <  */: {
			if (exp1_const&&exp2_const) {
				fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,exp1_value);
				fprintf(fp_inter, "BGE t%d %d WHILE_%d_END\n", reg_tmp,exp2_value, judge_index);
			}
			else if (exp1_const && !exp2_const) {
				fprintf(fp_inter, "BLE t%d %d WHILE_%d_END\n", exp2_counter, exp1_value, judge_index);
			}
			else if (!exp1_const&&exp2_const) {
				fprintf(fp_inter, "BGE t%d %d WHILE_%d_END\n", exp1_counter, exp2_value, judge_index);
			}
			else {
				fprintf(fp_inter, "BGE t%d t%d WHILE_%d_END\n", exp1_counter, exp2_counter, judge_index);
			}
			break;
		}
		case 1/* <= */: {
			if (exp1_const&&exp2_const) {
				fprintf(fp_inter, "LI t%d = %d\n",reg_tmp, exp1_value);
				fprintf(fp_inter, "BGT t%d %d WHILE_%d_END\n", reg_tmp,exp2_value, judge_index);
			}
			else if (exp1_const && !exp2_const) {
				fprintf(fp_inter, "BLT t%d %d WHILE_%d_END\n", exp2_counter, exp1_value, judge_index);
			}
			else if (!exp1_const&&exp2_const) {
				fprintf(fp_inter, "BGT t%d %d WHILE_%d_END\n", exp1_counter, exp2_value, judge_index);
			}
			else {
				fprintf(fp_inter, "BGT t%d t%d WHILE_%d_END\n", exp1_counter, exp2_counter, judge_index);
			}
			break;
		}
		case 2/* >  */: {
			if (exp1_const&&exp2_const) {
				fprintf(fp_inter, "LI t%d = %d\n",reg_tmp,exp1_value);
				fprintf(fp_inter, "BLE t%d %d WHILE_%d_END\n", reg_tmp,exp2_value, judge_index);
			}
			else if (exp1_const && !exp2_const) {
				fprintf(fp_inter, "BGE t%d %d WHILE_%d_END\n", exp2_counter, exp1_value, judge_index);
			}
			else if (!exp1_const&&exp2_const) {
				fprintf(fp_inter, "BLE t%d %d WHILE_%d_END\n", exp1_counter, exp2_value, judge_index);
			}
			else {
				fprintf(fp_inter, "BLE t%d t%d WHILE_%d_END\n", exp1_counter, exp2_counter, judge_index);
			}
			break;
		}
		case 3/* >= */: {
			if (exp1_const&&exp2_const) {
				fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,exp1_value);
				fprintf(fp_inter, "BLT t%d %d WHILE_%d_END\n", reg_tmp,exp2_value, judge_index);
			}
			else if (exp1_const && !exp2_const) {
				fprintf(fp_inter, "BGT t%d %d WHILE_%d_END\n", exp2_counter, exp1_value, judge_index);
			}
			else if (!exp1_const&&exp2_const) {
				fprintf(fp_inter, "BLT t%d %d WHILE_%d_END\n", exp1_counter, exp2_value, judge_index);
			}
			else {
				fprintf(fp_inter, "BLT t%d t%d WHILE_%d_END\n", exp1_counter, exp2_counter, judge_index);
			}
			break;
		}
		case 4/* != */: {
			if (exp1_const&&exp2_const) {
				fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,exp1_value);
				fprintf(fp_inter, "BEQ t%d %d WHILE_%d_END\n", reg_tmp,exp2_value, judge_index);
			}
			else if (exp1_const && !exp2_const) {
				fprintf(fp_inter, "BEQ t%d %d WHILE_%d_END\n", exp2_counter, exp1_value, judge_index);
			}
			else if (!exp1_const&&exp2_const) {
				fprintf(fp_inter, "BEQ t%d %d WHILE_%d_END\n", exp1_counter, exp2_value, judge_index);
			}
			else {
				fprintf(fp_inter, "BEQ t%d t%d WHILE_%d_END\n", exp1_counter, exp2_counter, judge_index);
			}
			break;
		}
		case 5/* == */: {
			if (exp1_const&&exp2_const) {
				fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,exp1_value);
				fprintf(fp_inter, "BNE t%d %d WHILE_%d_END\n", reg_tmp,exp2_value, judge_index);
			}
			else if (exp1_const && !exp2_const) {
				fprintf(fp_inter, "BNE t%d %d WHILE_%d_END\n", exp2_counter, exp1_value, judge_index);
			}
			else if (!exp1_const&&exp2_const) {
				fprintf(fp_inter, "BNE t%d %d WHILE_%d_END\n", exp1_counter, exp2_value, judge_index);
			}
			else {
				fprintf(fp_inter, "BNE t%d t%d WHILE_%d_END\n", exp1_counter, exp2_counter, judge_index);
			}
			break;
		}
		}
	}
	else{
		switch (operatorType) {
		case 0/* <  */: {
			if (exp1_const&&exp2_const) {
				fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,exp1_value);
				fprintf(fp_inter, "BGE t%d %d IF_%d_END\n",reg_tmp, exp2_value, judge_index);
			}
			else if (exp1_const && !exp2_const) {
				fprintf(fp_inter, "BLE t%d %d IF_%d_END\n", exp2_counter, exp1_value, judge_index);
			}
			else if (!exp1_const&&exp2_const) {
				fprintf(fp_inter, "BGE t%d %d IF_%d_END\n", exp1_counter, exp2_value, judge_index);
			}
			else {
				fprintf(fp_inter, "BGE t%d t%d IF_%d_END\n", exp1_counter, exp2_counter, judge_index);
			}
			break;
		}
		case 1/* <= */: {
			if (exp1_const&&exp2_const) {
				fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,exp1_value);
				fprintf(fp_inter, "BGT t%d %d IF_%d_END\n", reg_tmp,exp2_value, judge_index);
			}
			else if (exp1_const && !exp2_const) {
				fprintf(fp_inter, "BLT t%d %d IF_%d_END\n", exp2_counter, exp1_value, judge_index);
			}
			else if (!exp1_const&&exp2_const) {
				fprintf(fp_inter, "BGT t%d %d IF_%d_END\n", exp1_counter, exp2_value, judge_index);
			}
			else {
				fprintf(fp_inter, "BGT t%d t%d IF_%d_END\n", exp1_counter, exp2_counter, judge_index);
			}
			break;
		}
		case 2/* >  */: {
			if (exp1_const&&exp2_const) {
				fprintf(fp_inter, "LI t%d = %d\n",reg_tmp, exp1_value);
				fprintf(fp_inter, "BLE t%d %d IF_%d_END\n",reg_tmp, exp2_value, judge_index);
			}
			else if (exp1_const && !exp2_const) {
				fprintf(fp_inter, "BGE t%d %d IF_%d_END\n", exp2_counter, exp1_value, judge_index);
			}
			else if (!exp1_const&&exp2_const) {
				fprintf(fp_inter, "BLE t%d %d IF_%d_END\n", exp1_counter, exp2_value, judge_index);
			}
			else {
				fprintf(fp_inter, "BLE t%d t%d IF_%d_END\n", exp1_counter, exp2_counter, judge_index);
			}
			break;
		}
		case 3/* >= */: {
			if (exp1_const&&exp2_const) {
				fprintf(fp_inter, "LI t%d = %d\n",reg_tmp, exp1_value);
				fprintf(fp_inter, "BLT t%d %d IF_%d_END\n", reg_tmp,exp2_value, judge_index);
			}
			else if (exp1_const && !exp2_const) {
				fprintf(fp_inter, "BGT t%d %d IF_%d_END\n", exp2_counter, exp1_value, judge_index);
			}
			else if (!exp1_const&&exp2_const) {
				fprintf(fp_inter, "BLT t%d %d IF_%d_END\n", exp1_counter, exp2_value, judge_index);
			}
			else {
				fprintf(fp_inter, "BLT t%d t%d IF_%d_END\n", exp1_counter, exp2_counter, judge_index);
			}
			break;
		}
		case 4/* != */: {
			if (exp1_const&&exp2_const) {
				fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,exp1_value);
				fprintf(fp_inter, "BEQ t%d %d IF_%d_END\n", reg_tmp,exp2_value, judge_index);
			}
			else if (exp1_const && !exp2_const) {
				fprintf(fp_inter, "BEQ t%d %d IF_%d_END\n", exp2_counter, exp1_value, judge_index);
			}
			else if (!exp1_const&&exp2_const) {
				fprintf(fp_inter, "BEQ t%d %d IF_%d_END\n", exp1_counter, exp2_value, judge_index);
			}
			else {
				fprintf(fp_inter, "BEQ t%d t%d IF_%d_END\n", exp1_counter, exp2_counter, judge_index);
			}
			break;
		}
		case 5/* == */: {
			if (exp1_const&&exp2_const) {
				fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,exp1_value);
				fprintf(fp_inter, "BNE t%d %d IF_%d_END\n", reg_tmp,exp2_value, judge_index);
			}
			else if (exp1_const && !exp2_const) {
				fprintf(fp_inter, "BNE t%d %d IF_%d_END\n", exp2_counter, exp1_value, judge_index);
			}
			else if (!exp1_const&&exp2_const) {
				fprintf(fp_inter, "BNE t%d %d IF_%d_END\n", exp1_counter, exp2_value, judge_index);
			}
			else {
				fprintf(fp_inter, "BNE t%d t%d IF_%d_END\n", exp1_counter, exp2_counter, judge_index);
			}
			break;
		}
		}
	}
	if (!exp1_const) {
		releaseRegCounter(exp1_counter);
	}
	if(!exp2_const){
		releaseRegCounter(exp2_counter);
	}
	releaseRegCounter(reg_tmp);
}
/*switch instruction*/
void interPrintSwitchStart(int *switch_index) {
	*switch_index = switch_counter++;
	fprintf(fp_inter, "LABEL SWITCH_%d_START:\n", *switch_index);
}
void interPrintSwitchEnd(int switch_index) {
	fprintf(fp_inter, "LABEL SWITCH_%d_END:\n", switch_index);
}
void interPrintDefault(switch_index) {
	fprintf(fp_inter, "LABEL DEFAULT_%d:\n", switch_index);
}
void interPrintCaseJudge(int case_index, int switch_index,
	int const_value,int const_type,
	int exp_type,int exp_const,int exp_value,int exp_counter) 
{
	int reg_tmp = newRegCounter();
	if (exp_type != const_type) {
		//err case与switch的表达式类型不一致
		err(38);
		return;
	}
	if (exp_const) {
		fprintf(fp_inter, "LI t%d = %d\n",reg_tmp,exp_value);
		fprintf(fp_inter,"BNE t%d %d SWITCH%d_CASE%d_END\n",reg_tmp,const_value,switch_index,case_index);
	}
	else {
		fprintf(fp_inter, "BNE t%d %d SWITCH%d_CASE%d_END\n", exp_counter,const_value, switch_index, case_index);
	}
	releaseRegCounter(reg_tmp);
}
void interPrintCaseEnd(int case_index, int switch_index) {
	fprintf(fp_inter,"LABEL SWITCH%d_CASE%d_END:\n", switch_index, case_index);
}
void interPrintGotoSwitchEnd(int switch_index) {
	fprintf(fp_inter, "J SWITCH_%d_END\n",switch_index);
}
/*fun use instruction*/
void interPrintFUNUSE(char *funname,int funnamelen,int funsize) {
	fprintf(fp_inter, "FUNUSE %d ",funsize+40);
	for (int i = 0; i < funnamelen; i++) {
		fprintf(fp_inter, "%c", funname[i]);
	}
	fprintf(fp_inter, "\n");
}
void interPrintFUNJMP(char *funname, int funnamelen) {
	fprintf(fp_inter, "JAL FUN_");
	for (int i = 0; i < funnamelen; i++) {
		fprintf(fp_inter, "%c",funname[i]);
	}
	fprintf(fp_inter, "\n");
}
void interPrintPara(int para_offset,int exp_type,int exp_const,int exp_value,int exp_counter) {
	int reg_tmp = newRegCounter();
	if (exp_const) {
		if (exp_type == INT) {
			fprintf(fp_inter, "LI t%d = %d\n",reg_tmp,exp_value);
			fprintf(fp_inter, "SW t%d %d(fp)\n",reg_tmp,para_offset+40);
		}
		else {
			fprintf(fp_inter, "LI t%d = %d\n", reg_tmp,exp_value);
			fprintf(fp_inter, "SB t%d %d(fp)\n", reg_tmp,para_offset+40);
		}
	}
	else {
		if (exp_type == INT) {
			fprintf(fp_inter, "SW t%d %d(fp)\n", exp_counter,para_offset+40);
		}
		else {
			fprintf(fp_inter, "SB t%d %d(fp)\n", exp_counter,para_offset+40);
		}
	}
	releaseRegCounter(reg_tmp);
}
/*first exp with "-"*/
void interPrintMinusCounter(int *counter, int addflag) {
	if (addflag != 1) {
		fprintf(fp_inter,"SUB t%d = 0 - t%d\n", *counter, *counter);
	}
}

void interPrintGLOCSTSTART() {
	fprintf(fp_inter,"GLOCSTSTART\n");
}
void interPrintGLOCSTEND() {
	fprintf(fp_inter,"GLOCSTEND\n");
}

void interPrintFUNSAVE() {//ra
	int offset = cursymtable->usespace;
	fprintf(fp_inter,"SW ra %d(sp)\n",offset+4+40);
}