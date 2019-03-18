#include "translate.h"

char final_file[MAX_FILE_LEN];
char final_file2[MAX_FILE_LEN];
FILE *fp_final;
FILE *fp_int;
FILE *fp_final2;
char line[LIN_MAX_LEN];
void finalPrintStart() {
	printf("请输入最终代码的文件路径（注：windows下需要\\双斜杠）：\n");
	gets(final_file);
	printf("请输入最终代码(优化后）的文件路径（注：windows下需要\\双斜杠）：\n");
	gets(final_file2);
	return;
}


int jdg(char *name2, int len) {
	int i;
	for (i = 0; i < len; i++) {
		if (line[i] != name2[i]) {
			break;
		}
	}
	if (i == len) {
		return 1;
	}
	else {
		return 0;
	}
}

void translate() {
	if (jdg("GLOCST ", 7)) {
		fprintf(fp_final, ".data\n");
		int j;
		for (j = 7; line[j] != ' '; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, " : .space %c\n", line[j + 1]);
	}
	else if (jdg("GLOCSTASS", 9)) {
		fprintf(fp_final, ".text\n");
	}
	else if (jdg("GLOCSTSTART", 11)) {
		//do nothing
	}
	else if (jdg("GLOCSTEND", 9)) {
		fprintf(fp_final, ".text\n");
	}
	else if (jdg("GLOVARSTART", 11)) {
		fprintf(fp_final, ".data\n");
	}
	else if (jdg("GLOVAREND", 9)) {
		int index = searchFun("main", 4);
		int offset = ftable->fun[index].stp->usespace;
		fprintf(fp_final, ".text\n");
		fprintf(fp_final, "sub $sp,$sp,%d\n",offset+8);
		fprintf(fp_final,"jal FUN_main\n");
		fprintf(fp_final, "li $v0,10\n");
		fprintf(fp_final, "syscall\n");
	}
	else if (jdg("GLOVAR ", 7)) {
		int j = 7;
		for (j; line[j] != ' '; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, " : .space ");
		for (j = j + 1; line[j] != '\n' &&line[j]!='\0' &&line[j] != '\0' &&line[j] != '\0' &&line[j] != '\0'; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("LABEL ", 6)) {
		int j = 6;
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("PRTSTR ", 7)) {
		int j = 7;
		fprintf(fp_final, "li $v0,11\n");
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			fprintf(fp_final, "li $a0,%d\n", line[j]);
			fprintf(fp_final, "syscall\n");
		}
	}
	else if (jdg("FUNUSE ", 7)) {
		int tmp = 0;
		int j = 7;
		for (j; line[j] != ' '; j++) {
			tmp *= 10;
			tmp += line[j] - '0';
		}
		fprintf(fp_final, "subu $fp,$sp,%d\n", tmp + 8);
	}
	else if (jdg("SYSCALL", 7)) {
		fprintf(fp_final, "syscall\n");
	}
	else if (jdg("LI ", 3)) {
		int j = 3;
		fprintf(fp_final, "li $");
		for (j; line[j] != ' '; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, ",");
		for (j = j + 3; line[j] != '\n' &&line[j]!='\0'; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("SW ", 3)) {
		int j = 3,flag_tmp =1;
		fprintf(fp_final, "sw $");
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			if (line[j] == ' ') {
				if (flag_tmp) {
					fprintf(fp_final, ",");
					flag_tmp = 0;
				}
			}
			else if (line[j] == '+') {
				fprintf(fp_final, " + ");
			}
			else if (line[j] == '(') {
				fprintf(fp_final, "($");
			}
			else {
				fprintf(fp_final, "%c", line[j]);
			}
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("LW ", 3)) {
		int j = 3;
		fprintf(fp_final, "lw $");
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			if (line[j] == '=') {
				fprintf(fp_final, ",");
			}
			else if (line[j] == ' ') {
				//不输出
			}
			else if (line[j] == '+') {
				fprintf(fp_final, " + ");
			}
			else if (line[j] == '(') {
				fprintf(fp_final, "($");
			}
			else {
				fprintf(fp_final, "%c", line[j]);
			}
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("SB ", 3)) {
		int j = 3,flag_tmp =1;
		fprintf(fp_final, "sb $");
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			if (line[j] == ' ') {
				if (flag_tmp) {
					fprintf(fp_final, ",");
					flag_tmp = 0;
				}
			}
			else if (line[j] == '+') {
				fprintf(fp_final, " + ");
			}
			else if (line[j] == '(') {
				fprintf(fp_final, "($");
			}
			else {
				fprintf(fp_final, "%c", line[j]);
			}
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("LB ", 3)) {
		int j = 3;
		fprintf(fp_final, "lb $");
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			if (line[j] == '=') {
				fprintf(fp_final, ",");
			}
			else if (line[j] == ' ') {
				//不输出
			}
			else if (line[j] == '+') {
				fprintf(fp_final, " + ");
			}
			else if (line[j] == '(') {
				fprintf(fp_final, "($");
			}
			else {
				fprintf(fp_final, "%c", line[j]);
			}
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("J ", 2)) {
		fprintf(fp_final, "j ");
		int j = 2;
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("JR ", 3)) {
		fprintf(fp_final, "jr $ra\n");
	}
	else if (jdg("JAL ", 4)) {
		fprintf(fp_final, "sw $sp,-8($sp)\n");
		fprintf(fp_final, "move $sp,$fp\n");
		fprintf(fp_final, "jal ");
		int j = 4;
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, "\n");

	}
	else if (jdg("MOVE ", 5)) {
		fprintf(fp_final, "move $");
		int j = 5;
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			if (line[j] == '=') {
				fprintf(fp_final, ",$");
			}
			else if (line[j] == ' ') {
				//print nothing
			}
			else {
				fprintf(fp_final, "%c", line[j]);
			}
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("BLE ", 4)) {
		fprintf(fp_final, "ble $");
		int j = 4;
		for (j; line[j] != ' '; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, ",");
		j++;
		if (line[j] == '-' || (line[j] <= '9'&&line[j] >= 0)) {
			//print nothing
		}
		else {
			fprintf(fp_final, "$");
		}
		for (j; line[j] != ' '; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, ",");
		j++;
		for (j; line[j] != '\n'&&line[j]!='\0'; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("BGE ", 4)) {
	fprintf(fp_final, "bge $");
	int j = 4;
	for (j; line[j] != ' '; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, ",");
	j++;
	if (line[j] == '-' || (line[j] <= '9'&&line[j] >= 0)) {
		//print nothing
	}
	else {
		fprintf(fp_final, "$");
	}
	for (j; line[j] != ' '; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, ",");
	j++;
	for (j; line[j] != '\n'&&line[j] != '\0'; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, "\n");
	}
	else if (jdg("BLT ", 4)) {
	fprintf(fp_final, "blt $");
	int j = 4;
	for (j; line[j] != ' '; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, ",");
	j++;
	if (line[j] == '-' || (line[j] <= '9'&&line[j] >= 0)) {
		//print nothing
	}
	else {
		fprintf(fp_final, "$");
	}
	for (j; line[j] != ' '; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, ",");
	j++;
	for (j; line[j] != '\n'&&line[j] != '\0'; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, "\n");
	}
	else if (jdg("BGT ", 4)) {
	fprintf(fp_final, "bgt $");
	int j = 4;
	for (j; line[j] != ' '; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, ",");
	j++;
	if (line[j] == '-' || (line[j] <= '9'&&line[j] >= 0)) {
		//print nothing
	}
	else {
		fprintf(fp_final, "$");
	}
	for (j; line[j] != ' '; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, ",");
	j++;
	for (j; line[j] != '\n'&&line[j] != '\0'; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, "\n");
	}
	else if (jdg("BEQ ", 4)) {
	fprintf(fp_final, "beq $");
	int j = 4;
	for (j; line[j] != ' '; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, ",");
	j++;
	if (line[j] == '-' || (line[j] <= '9'&&line[j] >= 0)) {
		//print nothing
	}
	else {
		fprintf(fp_final, "$");
	}
	for (j; line[j] != ' '; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, ",");
	j++;
	for (j; line[j] != '\n'&&line[j] != '\0'; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, "\n");
	}
	else if (jdg("BNE ", 4)) {
	fprintf(fp_final, "bne $");
	int j = 4;
	for (j; line[j] != ' '; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, ",");
	j++;
	if (line[j] == '-' || (line[j] <= '9'&&line[j] >= 0)) {
		//print nothing
	}
	else {
		fprintf(fp_final, "$");
	}
	for (j; line[j] != ' '; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, ",");
	j++;
	for (j; line[j] != '\n'&&line[j] != '\0'; j++) {
		fprintf(fp_final, "%c", line[j]);
	}
	fprintf(fp_final, "\n");
	}
	else if (jdg("BEQZ ", 5)) {
		fprintf(fp_final, "beqz $");
		int j = 5;
		for (j; line[j] != ' '; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, ",");
		j++;
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("MUL ", 4)) {
		fprintf(fp_final, "mulu $");
		int j = 4;
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			if (line[j] == '=' || line[j] == '*') {
				fprintf(fp_final, ",$");
			}
			else if (line[j] == ' ') {
				//do nothing
			}
			else {
				fprintf(fp_final, "%c", line[j]);
			}
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("DIV ", 4)) {
		fprintf(fp_final, "divu $");
		int j = 4;
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			if (line[j] == '=' || line[j] == '/') {
				fprintf(fp_final, ",$");
			}
			else if (line[j] == ' ') {
				//do nothing
			}
			else {
				fprintf(fp_final, "%c", line[j]);
			}
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("ADD ", 4)) {
		fprintf(fp_final, "addu $");
		int j = 4;
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			if (line[j] == '=' || line[j] == '+') {
				fprintf(fp_final, ",$");
			}
			else if (line[j] == ' ') {
				//do nothing
			}
			else {
				fprintf(fp_final, "%c", line[j]);
			}
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("SUB ", 4)) {
		fprintf(fp_final, "subu $");
		int j = 4;
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			if (line[j] == '=' || line[j] == '-') {
				fprintf(fp_final, ",$");
			}
			else if (line[j] == ' ') {
				//do nothing
			}
			else {
				fprintf(fp_final, "%c", line[j]);
			}
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("MULI ", 5)) {
		fprintf(fp_final, "mulu $");
		int j = 5;
		for (j; line[j] != '*'; j++) {
			if (line[j] == '=') {
				fprintf(fp_final, ",$");
			}
			else if (line[j] == ' ') {
				//do nothing
			}
			else {
				fprintf(fp_final, "%c", line[j]);
			}
		}
		fprintf(fp_final, ",");
		j += 2;
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("DIVI ", 5)) {
		fprintf(fp_final, "divu $");
		int j = 5;
		for (j; line[j] != '/'; j++) {
			if (line[j] == '=') {
				fprintf(fp_final, ",$");
			}
			else if (line[j] == ' ') {
				//do nothing
			}
			else {
				fprintf(fp_final, "%c", line[j]);
			}
		}
		fprintf(fp_final, ",");
		j += 2;
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("SUBI ", 5)) {
		fprintf(fp_final, "sub $");
		int j = 5;
		for (j; line[j] != '-'; j++) {
			if (line[j] == '=') {
				fprintf(fp_final, ",$");
			}
			else if (line[j] == ' ') {
				//do nothing
			}
			else {
				fprintf(fp_final, "%c", line[j]);
			}
		}
		fprintf(fp_final, ",");
		j += 2;
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, "\n");
	}
	else if (jdg("ADDI ", 5)) {
		fprintf(fp_final, "addu $");
		int j = 5;
		for (j; line[j] != '+'; j++) {
			if (line[j] == '=') {
				fprintf(fp_final, ",$");
			}
			else if (line[j] == ' ') {
				//do nothing
			}
			else {
				fprintf(fp_final, "%c", line[j]);
			}
		}
		fprintf(fp_final, ",");
		j += 2;
		for (j; line[j] != '\n' &&line[j]!='\0'; j++) {
			fprintf(fp_final, "%c", line[j]);
		}
		fprintf(fp_final, "\n");
	}
	else {
		fprintf(fp_final, "%s unnkonwn i\n",line);
	}

}

void finalPrintProceed() {
	fp_int = fopen(inter_file, "r");
	fp_final = fopen(final_file, "w");
	if (fp_final == NULL) {
		perror("can't open final_file");
	}
	if (fp_int == NULL) {
		perror("can't open inter_file");
	}
	while (!feof(fp_int)) {
		fgets(line, LIN_MAX_LEN, fp_int);
		translate();
	}
	if (fclose(fp_int) == EOF) {
		perror("can't close inter_file");
	}
	if(fclose(fp_final) == EOF) {
		perror("can't close final_file");
	}
	finalcpy();
	return;
}

void finalcpy() {
	char *buff;
	int ret;
	fp_final = fopen(final_file, "r");
	fp_final2 = fopen(final_file2, "w");
	if (fp_final == NULL || fp_final2 == NULL) {
		perror("open failed!\n");
		return;
	}
	buff = (char *)malloc(BUFFSIZE);
	if (buff == NULL) {
		printf("buff filed\n");
		return;
	}
	while (1) {
		ret = fread(buff, 1, BUFFSIZE, fp_final);
		if (ret != BUFFSIZE) {
			fwrite(buff, ret, 1, fp_final2);
		}
		else {
			fwrite(buff, BUFFSIZE, 1, fp_final2);
		}
		if (feof(fp_final)) {
			break;
		}
	}
	fclose(fp_final);
	fclose(fp_final2);
	free(buff);
	return;
}