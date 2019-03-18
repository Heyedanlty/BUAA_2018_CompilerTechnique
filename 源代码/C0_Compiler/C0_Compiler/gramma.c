#include "gramma.h"


int gramma_debug = 0;


int isGlobalConstDeclare() {//ȫ�ֳ���˵��
	while (type == RESSYM && value == CONST) {
		if(nextsym()==EOF){err(43);}
		isGlobalConstDefination();
		if (type == SYMSYM && value == ';') {
			if(nextsym()==EOF){err(43);}
		}
		else {
			//err ȱ�ٷֺ�
			err(5);
			__nextSemicolon();
			if(nextsym()==EOF){err(43);}
		}
	}
	return 1;
}
void isGlobalConstDefination() {//ȫ�ֳ�������
	char symname[IDE_MAX_LEN];
	int symlen, symvalue;

	if (gramma_debug) {
		printf("%d:", line_number);
		printf("ȫ�ֳ����������\n");
	}
	if (type == RESSYM) {
		if (value == INT) {
			do {
				if(nextsym()==EOF){err(43);}
				if (!isIdentifier(symname, &symlen)) {
					__nextCommaOrSemicolon();
				}
				else {
					if (type == SYMSYM && value == '=') {
						if(nextsym()==EOF){err(43);}
						if (isInteger(&symvalue)) {
							addSym(symname, symlen, CONSTANT, INT, NOTARR, ZERO, symvalue,1);
							//@
							interPrintGLOCST(symname,symlen,INT,symvalue);
						}
						else {
							//need integer
							err(27);
							__nextCommaOrSemicolon();
						}
					}
					else {
						//need =
						err(7);
						__nextCommaOrSemicolon();
					}
				}
			} while (type == SYMSYM && value == ',');
		}
		else if (value == CHAR) {
			do {
				if(nextsym()==EOF){err(43);}
				if (!isIdentifier(symname, &symlen)) {
					__nextCommaOrSemicolon();
				}
				else {
					if (type == SYMSYM && value == '=') {
						if(nextsym()==EOF){err(43);}
						if (isChar(&symvalue)) {
							addSym(symname, symlen, CONSTANT, CHAR, NOTARR, ZERO, symvalue,1);
							//@
							interPrintGLOCST(symname, symlen, CHAR, symvalue);
						}
						else {
							//err need char
							err(28);
							__nextCommaOrSemicolon();
						}
					}
					else {
						//need =
						err(7);
						__nextCommaOrSemicolon();
					}
				}
			} while (type == SYMSYM && value == ',');
		}
		else {
			//err �����ִ���
			err(7);
			__nextSemicolon();
			return;
		}
	}
	else {
		//err ȱ�����ͱ�����
		err(8);
		__nextSemicolon();
		return;
	}
}
int isConstDeclare() {//����˵��
	while (type == RESSYM && value == CONST) {
		if(nextsym()==EOF){err(43);}
		isConstDefination();
		if (type == SYMSYM && value == ';') {
			if(nextsym()==EOF){err(43);}
		}
		else {
			//err ȱ�ٷֺ�
			err(6);
			__nextSemicolon();
			if(nextsym()==EOF){err(43);}
		}
	}
	return 1;
}
void isConstDefination() {//��������
	char symname[IDE_MAX_LEN];
	int symlen,symvalue;

	if (gramma_debug) {
		printf("%d:", line_number);
		printf("�����������\n");
	}
	if (type == RESSYM) {
		if (value == INT) {
			do {
				if(nextsym()==EOF){err(43);}
				if (!isIdentifier(symname,&symlen)) {
					__nextCommaOrSemicolon();
				}
				else {
					if (type == SYMSYM && value == '=') {
						if(nextsym()==EOF){err(43);}
						if (isInteger(&symvalue)) {
							addSym(symname,symlen,CONSTANT,INT,NOTARR,ZERO,symvalue,1);
							//@
							int index = searchSym(symname, symlen);
							interPrintFUNCST(INT, symvalue,cursymtable->sym[index].offset);
						}
						else {
							//need integer
							err(27);
							__nextCommaOrSemicolon();
						}
					}
					else {
						//need =
						err(7);
						__nextCommaOrSemicolon();
					}
				}
			} while (type == SYMSYM && value == ',');
		}
		else if (value == CHAR) {
			do {
				if(nextsym()==EOF){err(43);}
				if (!isIdentifier(symname, &symlen)) {
					__nextCommaOrSemicolon();
				}
				else {
					if (type == SYMSYM && value == '=') {
						if(nextsym()==EOF){err(43);}
						if (isChar(&symvalue)) {
							addSym(symname, symlen, CONSTANT, CHAR, NOTARR, ZERO, symvalue,1);
							//@
							int index = searchSym(symname, symlen);
							interPrintFUNCST(CHAR, symvalue, cursymtable->sym[index].offset);
						}
						else {
							//err need char
							err(28);
							__nextCommaOrSemicolon();
						}
					}
					else {
						//need =
						err(7);
						__nextCommaOrSemicolon();
					}
				}
			} while (type == SYMSYM && value == ',');
		}
		else {
			//err �����ִ���
			err(7);
			__nextSemicolon();
			return;
		}
	}
	else {
		//err ȱ�����ͱ�����
		err(8);
		__nextSemicolon();
		return;
	}
}
void isVariableDeclare() {//����˵��
	int symtype;
	while (type == RESSYM && (value == INT || value == CHAR)) {
		symtype = value;
		if (gramma_debug) {
			printf("%d:", line_number);
			printf("�����������\n");
		}
		do {
			if(nextsym()==EOF){err(43);}
			isVariableDefination(symtype);
		} while (type == SYMSYM && value == ',');
		if (type == SYMSYM && value == ';') {
			if(nextsym()==EOF){err(43);}
		}
		else {
			//need ;
			err(5);
			__nextSemicolon();
			if(nextsym()==EOF){err(43);}
		}
	}

}
void isVariableDefination(int symtype) {//��������
	char symname[IDE_MAX_LEN];
	int symlen, upbound;

	if (!isIdentifier(symname,&symlen)) {
		//need an identifier
		err(14);
		__nextCommaOrSemicolon();
		return;
	}
	if (type == SYMSYM && value == '[') {
		if(nextsym()==EOF){err(43);}
		if (!isUnsignedInteger(&upbound)) {
			__nextCommaOrSemicolon();
			return;
		}
		else {
			if (type == SYMSYM && value == ']') {
				if(nextsym()==EOF){err(43);}
			}
			else {
				//need ]
				err(9);
				__nextCommaOrSemicolon();
				return;
			}
			addSym(symname, symlen, VARIABLE, symtype, ARR, upbound, ZERO,0);
			//@
		}
	}
	else {//��������
		addSym(symname,symlen,VARIABLE,symtype,NOTARR,ZERO,ZERO,0);
		//@
	}
}
void isDefFunWithValue() {//�з���ֵ��������
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("�з���ֵ��������\n");
	}
	resetRegPool();
	if (!isDeclareHead()) {
		__nextReservedSymbol();
		return;
	}
	if (type == SYMSYM && value == '(') {
		if(nextsym()==EOF){err(43);}
		if (!isParameterTable()) {
			__nextReservedSymbol();
			return;
		}
		if (type == SYMSYM && value == ')') {
			if(nextsym()==EOF){err(43);}
			if (type == SYMSYM && value == '{') {
				if(nextsym()==EOF){err(43);}
				isCompoundStatement();
				if (type == SYMSYM && value == '}') {
					if(nextsym()==EOF){err(43);}
					interPrintRETURN();
					/*interPrintFUNEND();*/
				}
				else {
					//err need}
					err(10);
					__nextReservedSymbol();
					return;
				}
			}
			else {
				//err need{
				err(11);
				__nextReservedSymbol();
				return;
			}
		}
		else {
			//err need��
			err(12);
			__nextReservedSymbol();
			return;
		}
	}
	else {
		//err need(
		err(13);
		__nextReservedSymbol();
		return;
	}
}
void isDefFunWithoutValue() {//�޷���ֵ���������Ӿ�
	char funname[IDE_MAX_LEN];
	int funnamelen;
	resetRegPool();
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("�޷���ֵ��������\n");
	}
	if (type == IDESYM) {
		if (!isIdentifier(funname,&funnamelen)) {
			__nextReservedSymbol();
			return;
		}
		insertFun(funname, funnamelen, VOID);
		interPrintFUNDEF(funname, funnamelen);
		if (type == SYMSYM && value == '(') {
			if(nextsym()==EOF){err(43);}
			if (!isParameterTable()) {
				__nextReservedSymbol();
				return;
			}
			if (type == SYMSYM && value == ')') {
				if(nextsym()==EOF){err(43);}
				if (type == SYMSYM && value == '{') {
					if(nextsym()==EOF){err(43);}
					isCompoundStatement();
					if (type == SYMSYM && value == '}') {
						if(nextsym()==EOF){err(43);}
						interPrintRETURN();
						/*interPrintFUNEND();*/
					}
					else {
						//need }
						err(10);
						__nextReservedSymbol();
						return;
					}
				}
				else {
					//need{
					err(11);
					__nextReservedSymbol();
					return;
				}
			}
			else {
				//need)
				err(12);
				__nextReservedSymbol();
				return;
			}
		}
		else {
			//need (
			err(13);
			__nextReservedSymbol();
			return;
		}
	}
	else {
		//need identifier
		err(14);
		__nextReservedSymbol();
		return;
	}

}
int isDeclareHead() {//����ͷ��//�������з���ֵ�ĺ�������
	char funname[IDE_MAX_LEN];
	int funnamelen;

	if (type == RESSYM) {
		if (value == INT) {
			if(nextsym()==EOF){err(43);}
			if (!isIdentifier(funname,&funnamelen)) {
				//need identifier
				err(14);
				return 0;
			}
			if (funnamelen == 4 && funname[0] == 'm'&&funname[1] == 'a'&&funname[2] == 'i'&&funname[3] == 'n') {
				//err need void main
				err(41);
				return 0;
			}
			insertFun(funname, funnamelen, INT);
			interPrintFUNDEF(funname, funnamelen);
			return 1;
		}
		else if (value == CHAR) {
			if(nextsym()==EOF){err(43);}
			if (!isIdentifier(funname,&funnamelen)) {
				//need identifier
				err(14);
				return 0;
			}
			insertFun(funname, funnamelen, CHAR);
			interPrintFUNDEF(funname, funnamelen);
			return 1;
		}
		else {
			//err ȱ�����ͱ����֡������ִ���
			err(8);
			return 0;
		}
	}
	else {
		//err invalid type ȱ�����ͱ�����
		err(8);
		return 0;
	}
}
int isParameterTable() {//������
	if (type == RESSYM && (value == INT || value == CHAR)) {
		if (!isParameter()) {
			return 0;
		}
		while (type == SYMSYM && value == ',') {
			if(nextsym()==EOF){err(43);}
			if (!isParameter()) {
				return 0;
			}
		}
	}
	return 1;
}
int isParameter() {//����
	char paraname[IDE_MAX_LEN];
	int paranamelen,paratype;
	if (!isTypeIdentifier(&paratype)) {
		return 0;
	}
	if (!isIdentifier(paraname,&paranamelen)) {
		return 0;
	}
	addPara(paraname, paranamelen, paratype,0);
	return 1;
}
int isTypeIdentifier(int *returntype) {//���ͱ�ʶ��
	if (type == RESSYM && (value == INT || value == CHAR)) {
		*returntype = value;
		if(nextsym()==EOF){err(43);}
	}
	else {
		//not a type identifier ȱ�����ͱ�����
		err(8);
		return 0;
	}
	return 1;
}
int isIdentifier(char *name,int *namelen) {//��ʶ��
	if (type == IDESYM) {
		*namelen = value;
		while (value > 0) {
			name[value - 1] = iden[value - 1];
			value--;
		}
		if(nextsym()==EOF){err(43);}
		return 1;
	}
	else {
		//not a identifier ȱ�ٱ�ʶ��
		err(14);
		return 0;
	}
}
void isCompoundStatement() {//�������
	isConstDeclare();
	isVariableDeclare();
	interPrintFUNSAVE();
	isStatementColumn();
	return;
}
void isStatementColumn() {//�����
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("�����\n");
	}
	while (type != SYMSYM || value != '}') {//���ú���ַ��ж��Ƿ���Ϊ���
		isStatement();
	}
	return;
}
void isStatement() {//���
	if (type == RESSYM && value == IF) {
		isIfStatement();
	}
	else if (type == RESSYM && value == WHILE) {
		isWhileStatement();
	}
	else if (type == SYMSYM && value == '{') {
		if(nextsym()==EOF){err(43);}
		isStatementColumn();
		if (type == SYMSYM && value == '}') {
			if(nextsym()==EOF){err(43);}
		}
		else {
			//need }
			err(10);
			return;
		}
	}
	else if (type == RESSYM && value == SWITCH) {
		isSwitchStatement();
	}
	else if (type == IDESYM) {
		char name_tmp[IDE_MAX_LEN];
		int namelen_tmp;
		isIdentifier(name_tmp,&namelen_tmp);
		if (type == SYMSYM && (value == '=' || value == '[')) {
			isAssignmentStatement(name_tmp,namelen_tmp);
			if (type == SYMSYM && value == ';') {
				if(nextsym()==EOF){err(43);}
			}
		}
		else if (type == SYMSYM && value == '(') {
			isUseFun(name_tmp,namelen_tmp);
			getTmpRegisters();
			if (type == SYMSYM && value == ';') {
				if(nextsym()==EOF){err(43);}
			}
			else {
				//need ;
				err(5);
				__nextSemicolon();
				return;
			}
		}
		else {
			//need =/(
			err(22);
			__nextSemicolon();
			return;
		}
	}
	else if (type == RESSYM && value == SCANF) {
		isScanfStatement();
		if (type == SYMSYM && value == ';') {
			if(nextsym()==EOF){err(43);}
		}
		else {
			//need ;
			err(5);
			__nextSemicolon();
			return;
		}
	}
	else if (type == RESSYM && value == PRINTF) {
		isPrintfStatement();
		if (type == SYMSYM && value == ';') {
			if(nextsym()==EOF){err(43);}
		}
		else {
			//need ;
			err(5);
			__nextSemicolon();
			return;
		}
	}
	else if (type == SYMSYM && value == ';') {
		if (gramma_debug) {
			printf("%d:", line_number);
			printf("�����");
		}
		if(nextsym()==EOF){err(43);}
	}
	else if (type == RESSYM && value == RETURN) {
		isReturnStatement();
		if (type == SYMSYM && value == ';') {
			if(nextsym()==EOF){err(43);}
		}
		else {
			//need ;
			err(5);
			__nextSemicolon();
			return;
		}
	}
	else {
		return;//not a statement(NULL)
	}
}
void isAssignmentStatement(char *leftname,int leftnamelen) {//��ֵ���
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("��ֵ���\n");
	}
	int index_tmp, global_flag;
	int lefttype, leftarr, leftconstant,leftoffset;
	int exp_type, exp_const, exp_value, exp_counter;
	int offset;
	index_tmp = searchSym(leftname, leftnamelen);
	if (index_tmp != -1) {
		leftoffset = cursymtable->sym[index_tmp].offset;
		leftconstant = cursymtable->sym[index_tmp].kind;
		lefttype = cursymtable->sym[index_tmp].type;
		leftarr = cursymtable->sym[index_tmp].array;
		global_flag = 0;
	}
	else {
		index_tmp = searchGlobalSym(leftname, leftnamelen);
		if (index_tmp != -1) {
			leftoffset = glosymtable->sym[index_tmp].offset;
			leftconstant = glosymtable->sym[index_tmp].kind;
			lefttype = glosymtable->sym[index_tmp].type;
			leftarr = glosymtable->sym[index_tmp].array;
			global_flag = 1;
		}
		else {
			//err δ����ı�ʶ��
			err(32);
			__nextSemicolon();
			return;
		}
	}
	if (type == SYMSYM && value == '=') {
		if (leftarr == ARR||leftconstant==CONSTANT) {
			//err ��ʶ��������ĸ�ֵ��ʽ
			err(37);
			__nextSemicolon();
			return;
		}
		if(nextsym()==EOF){err(43);}
		if (!isExpression(&exp_type,&exp_const,&exp_value,&exp_counter)) {
			__nextSemicolon();
			return;
		}
		if (lefttype != exp_type) {
			//err wrong type of assignment
			err(36);
			__nextSemicolon();
			return;
		}
		if (exp_const) {
			if (global_flag) {
				interPrintASSGLOCST(leftname,leftnamelen,exp_type,exp_value);
				glosymtable->sym[index_tmp].definite = 0;
				glosymtable->sym[index_tmp].value = exp_value;
			}
			else {
				offset = cursymtable->sym[index_tmp].offset;
				interPrintASSCURCST(exp_type,offset,exp_value);
				cursymtable->sym[index_tmp].definite = 0;
				cursymtable->sym[index_tmp].value = exp_value;
			}
		}
		else {
			if (global_flag) {
				interPrintASSGLOVAR(leftname,leftnamelen,exp_type,exp_counter);
				glosymtable->sym[index_tmp].definite = 0;
			}
			else {
				offset = cursymtable->sym[index_tmp].offset;
				interPrintASSCURVAR(exp_type,offset,exp_counter);
				cursymtable->sym[index_tmp].definite = 0;
			}
		}
	}
	else if (type == SYMSYM && value == '[') {
		int leftexp_type, leftexp_const, leftexp_value, leftexp_counter;
		if (leftarr == NOTARR) {
			//err δ����ı�ʶ��
			err(32);
			__nextSemicolon();
			return;
		}
		if(nextsym()==EOF){err(43);}
		if (!isExpression(&leftexp_type, &leftexp_const,&leftexp_value, &leftexp_counter)) {
			__nextSemicolon();
			return;
		}
		if (leftexp_type == CHAR) {
			//err ��Ҫ���ͱ��ʽ
			err(34);
			__nextSemicolon();
			return;
		}
		if (type == SYMSYM && value == ']') {
			if(nextsym()==EOF){err(43);}
			if (type == SYMSYM && value == '=') {
				if(nextsym()==EOF){err(43);}
				if (!isExpression(&exp_type, &exp_const, &exp_value, &exp_counter)) {
					__nextSemicolon();
					return;
				}
				if (exp_type != lefttype) {
					//err ��ֵ����������Ͳ�ͬ
					err(36);
					__nextSemicolon();
					return;
				}
				interPrintASSARR(global_flag,leftname,leftnamelen,exp_type,leftoffset,leftexp_const,leftexp_value,leftexp_counter,exp_const,exp_value,exp_counter);
				if (!leftexp_const) {
					releaseRegCounter(leftexp_counter);
				}
				if (!exp_const) {
					releaseRegCounter(exp_counter);
				}
			}
			else {
				//need =
				err(6);
				__nextSemicolon();
				return;
			}
		}
		else {
			//need ]
			err(9);
			__nextSemicolon();
			return;
		}
	}
	else {
		//need =/[
		err(23);
		__nextSemicolon();
		return;
	}
}
void isIfStatement() {//�������
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("�������\n");
	}
	int if_index;
	if (type == RESSYM && value == IF) {
		interPrintIfStart(&if_index);
		if(nextsym()==EOF){err(43);}
		if (type == SYMSYM && value == '(') {
			if(nextsym()==EOF){err(43);}
			if (!isCondition(IF,if_index)) {
				__nextSemicolon();
				return;
			}
			if (type == SYMSYM && value == ')') {
				if(nextsym()==EOF){err(43);}
				isStatement();
				interPrintIfEnd(if_index);
			}
			else {
				//need )
				err(12);
				__nextSemicolon();
				return;
			}
		}
		else {
			//need(
			err(13);
			__nextSemicolon();
			return;
		}
	}
	else {
		return;//not if statement
	}
}
int isCondition(int judge_type,int judge_index) {//����
	int operatorType;
	int exp1_type, exp1_const, exp1_value, exp1_counter;
	int exp2_type, exp2_const, exp2_value, exp2_counter;
	if (!isExpression(&exp1_type,&exp1_const,&exp1_value,&exp1_counter)) {
		return 0;
	}
	if (exp1_type == CHAR) {
		//err need intexp
		err(34);
		return 0;
	}
	if (isRelationOperator(&operatorType)) {
		if (!isExpression(&exp2_type, &exp2_const, &exp2_value, &exp2_counter)) {
			return 0;
		}
		if (exp2_type == CHAR) {
			//err need intexp
			err(34);
			return 0;
		}
		//@
		interPrintJudge2(judge_type,judge_index,operatorType,
			 exp1_const, exp1_value, exp1_counter,
			 exp2_const, exp2_value, exp2_counter);
		if (!exp1_const) {
			releaseRegCounter(exp1_counter);
		}
		if (!exp2_const) {
			releaseRegCounter(exp2_counter);
		}
		return 1;
	}
	interPrintJudge1(judge_type,judge_index, exp1_const, exp1_value, exp1_counter);
	//@
	if (!exp1_const) {
		releaseRegCounter(exp1_counter);
	}
	return 1;
}
void isWhileStatement() {//ѭ�����
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("ѭ�����\n");
	}
	int while_index;
	if (type == RESSYM && value == WHILE) {
		interPrintWhileStart(&while_index);
		if(nextsym()==EOF){err(43);}
		if (type == SYMSYM && value == '(') {
			if(nextsym()==EOF){err(43);}
			if (!isCondition(WHILE,while_index)) {
				__nextSemicolon();
				return;
			}
			if (type == SYMSYM && value == ')') {
				if(nextsym()==EOF){err(43);}
				isStatement();
				interPrintBackWhile(while_index);
				interPrintWhileEnd(while_index);
			}
			else {
				//need )
				err(12);
				__nextSemicolon();
				return;
			}
		}
		else {
			//need(
			err(13);
			__nextSemicolon();
			return;
		}
	}
	else {
		return;//not while statement
	}
}
void isSwitchStatement() {//������
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("������\n");
	}
	int switch_index;
	int exp_type, exp_const, exp_value, exp_counter;
	interPrintSwitchStart(&switch_index);
	if (type == RESSYM && value == SWITCH) {
		if(nextsym()==EOF){err(43);}
		if (type == SYMSYM && value == '(') {
			if(nextsym()==EOF){err(43);}
			if (!isExpression(&exp_type,&exp_const,&exp_value,&exp_counter)) {
				__nextSemicolon();
				return;
			}
			if (type == SYMSYM && value == ')') {
				if(nextsym()==EOF){err(43);} {
					if (type == SYMSYM && value == '{') {
						if(nextsym()==EOF){err(43);}
						if (!isCaseTable(switch_index,exp_type,exp_const,exp_value,exp_counter)) {
							__nextSemicolon();
							return;
						}
						if (!isDefault(switch_index)) {
							__nextSemicolon();
							return;
						}
						if (type == SYMSYM && value == '}') {
							if(nextsym()==EOF){err(43);}
							if (!exp_const) {
								releaseRegCounter(exp_counter);
							}
							interPrintSwitchEnd(switch_index);
						}
						else {
							//need }
							err(10);
							__nextSemicolon();
							return;
						}
					}
					else {
						//need {
						err(11);
						__nextSemicolon();
						return;
					}
				}
			}
			else {
				//need )
				err(12);
				__nextSemicolon();
				return;
			}
		}
		else {
			//need (
			err(13);
			__nextSemicolon();
			return;
		}
	}
	else {
		return;//not switch statment
	}
}
int isCaseTable(int switch_index,int exp_type,int exp_const, int exp_value,int exp_counter) {//�����
	if (!isCaseStatement(switch_index,exp_type,exp_const,exp_value,exp_counter)) {
		return 0;
	}
	while (type == RESSYM && value == CASE) {
		if (!isCaseStatement(switch_index,exp_type, exp_const, exp_value, exp_counter)) {
			return 0;
		}
	}
	return 1;
}
int isDefault(int switch_index) {//ȱʡ
	if (type == RESSYM && value == DEFAULT) {
		if (gramma_debug) {
			printf("%d:", line_number);
			printf("ȱʡ\n");
		}
		if(nextsym()==EOF){err(43);}
		if (type == SYMSYM && value == ':') {
			interPrintDefault(switch_index);
			if(nextsym()==EOF){err(43);}
			isStatement();
			return 1;
		}
		else {
			//need :
			err(16);
			return 0;
		}
	}
	interPrintDefault(switch_index);
	return 1;
}
int isCaseStatement(int switch_index,int exp_type, int exp_const, int exp_value, int exp_counter) {//��������
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("��������\n");
	}
	int constvalue, consttype;
	int case_index;
	interPrintGetCase(&case_index);
	if (type == RESSYM && value == CASE) {
		if(nextsym()==EOF){err(43);}
		if (!isConst(&constvalue,&consttype)) {
			//need a const
			err(29);
			return 0;
		}
		if (type == SYMSYM && value == ':') {
			interPrintCaseJudge(case_index,switch_index,constvalue,consttype,exp_type,exp_const,exp_value,exp_counter);
			if(nextsym()==EOF){err(43);}
			isStatement();
			interPrintGotoSwitchEnd(switch_index);
			interPrintCaseEnd(case_index,switch_index);
		}
		else {
			//need :
			err(16);
			return 0;
		}
	}
	else {
		return 1;//not case statement
	}
	return 1;
}
int isUseFunWithValue(char *funname,int funnamelen,int *fun_type) {//�з���ֵ�����������
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("�з���ֵ�����������\n");
	}
	int index_tmp;
	int funsize, paratype[MAX_PAR_NUM], paraoffset[MAX_PAR_NUM], numofpara;
	index_tmp = searchFun(funname, funnamelen);
	if (index_tmp == -1/*�����ں���*/) {
		//err no function
		err(30);
		__nextSemicolon();
		return 0;
	}
	if (ftable->fun[index_tmp].value == VOID) {
		//err use of void function
		err(31);
		__nextSemicolon();
		return 0;
	}
	funsize = ftable->fun[index_tmp].stp->usespace;
	numofpara = ftable->fun[index_tmp].stp->numofpara;
	for (int i = 0; i < numofpara; i++) {
		paraoffset[i] = ftable->fun[index_tmp].stp->sym[i].offset;
		paratype[i] = ftable->fun[index_tmp].stp->sym[i].type;
	}
	*fun_type = ftable->fun[index_tmp].value;//return the value type of the function using address
	if (type == SYMSYM && value == '(') {
		interPrintFUNUSE(funname, funnamelen, funsize);
		if(nextsym()==EOF){err(43);}
		if (!isValueParameterTable(paratype,paraoffset,numofpara,funname,funnamelen,funsize)) {
			__nextSemicolon();
			return 0;
		}
		if (type == SYMSYM && value == ')') {
			interPrintFUNUSE(funname, funnamelen, funsize);
			saveTmpRegisters();
			interPrintFUNJMP(funname, funnamelen);
			if(nextsym()==EOF){err(43);}
		}
		else {
			//need )
			err(12);
			__nextSemicolon();
			return 0;
		}
	}
	else {
		//need (
		err(13);
		__nextSemicolon();
		return 0;
	}
	return 1;
}
int isUseFun(char *funname,int funnamelen) {//�����������
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("�����������\n");
	}
	int index_tmp;
	int funsize, paratype[MAX_PAR_NUM], paraoffset[MAX_PAR_NUM], numofpara;
	index_tmp = searchFun(funname, funnamelen);
	if (index_tmp == -1) {
		//err no function
		err(30);
		__nextSemicolon();
		return 0;
	}
	funsize = ftable->fun[index_tmp].stp->usespace;
	numofpara = ftable->fun[index_tmp].stp->numofpara;
	for (int i = 0; i < numofpara; i++) {
		paraoffset[i] = ftable->fun[index_tmp].stp->sym[i].offset;
		paratype[i] = ftable->fun[index_tmp].stp->sym[i].type;
	}
	if (type == SYMSYM && value == '(') {
		interPrintFUNUSE(funname, funnamelen, funsize);
		if(nextsym()==EOF){err(43);}
		if (!isValueParameterTable(paratype,paraoffset,numofpara,funname,funnamelen,funsize)) {
			__nextSemicolon();
			return 0;
		}
		if (type == SYMSYM && value == ')') {
			interPrintFUNUSE(funname, funnamelen, funsize);
			saveTmpRegisters();
			interPrintFUNJMP(funname, funnamelen);
			if(nextsym()==EOF){err(43);}
		}
		else {
			//need )
			err(12);
			__nextSemicolon();
			return 0;
		}
	}
	else {
		//need (
		err(13);
		__nextSemicolon();
		return 0;
	}
	return 1;
}
//void isUseFunWithoutValue() {//�޷���ֵ�����������
//	if (gramma_debug) {
//		printf("%d:", line_number);
//		printf("�޷���ֵ�����������\n");
//	}
//	isIdentifier();
//	if (type == SYMSYM && value == '(') {
//		if(nextsym()==EOF){err(43);}
//		if (!isValueParameterTable()) {
//			__nextSemicolon();
//			return;
//		}
//		if (type == SYMSYM && value == ')') {
//			if(nextsym()==EOF){err(43);}
//		}
//		else {
//			//need )
//			err(12);
//			__nextSemicolon();
//			return;
//		}
//	}
//	else {
//		//need (
//		err(13);
//		__nextSemicolon();
//		return;
//	}
//}
int isValueParameterTable(int *paratype,int *paraoffset,int numofpara,char *funname,int funnamelen,int funsize) {//ֵ������
	int exp_type, exp_const, exp_value, exp_counter;
	int numnow = 0;
	if (type == SYMSYM && value == ')') {
		if (numofpara == 0) {
			return 1;
			//�޲�
		}
		else {
			//wrong amount of para
			err(39);
			return 0;
		}
		
	}
	else {
		if (!isExpression(&exp_type,&exp_const,&exp_value,&exp_counter)) {
			return 0;
		}
		numnow++;
		if (numnow > numofpara) {
			//wrong amount of para
			err(39);
			return 0;
		}
		if (paratype[numnow-1] != exp_type) {
			//wrong type of para
			err(40);
			return 0;
		}
		//@��Ӳ���
		interPrintFUNUSE(funname, funnamelen, funsize);
		interPrintPara(paraoffset[numnow-1], exp_type, exp_const, exp_value, exp_counter);
		if (!exp_const) {
			releaseRegCounter(exp_counter);
		}
		while (type == SYMSYM && value == ',') {
			if(nextsym()==EOF){err(43);}
			if (!isExpression(&exp_type, &exp_const, &exp_value, &exp_counter)) {
				return 0;
			}
			numnow++;
			if (numnow > numofpara) {
				//wrong amount of para
				err(39);
				return 0;
			}
			if (paratype[numnow-1] != exp_type) {
				//wrong type of para
				err(40);
				return 0;
			}
			//@��Ӳ���
			interPrintFUNUSE(funname, funnamelen, funsize);
			interPrintPara(paraoffset[numnow-1], exp_type, exp_const, exp_value, exp_counter);
			if (!exp_const) {
				releaseRegCounter(exp_counter);
			}
		}
		if (numnow != numofpara) {
			//wrong amount of para
			err(39);
			return 0;
		}
	}
	return 1;
}
void isScanfStatement() {//�����
	char idenname[IDE_MAX_LEN];
	int idennamelen,index_tmp;
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("�����\n");
	}
	if (type == RESSYM && value == SCANF) {
		if(nextsym()==EOF){err(43);}
		if (type == SYMSYM && value == '(') {
			do {
				if(nextsym()==EOF){err(43);}
				if (isIdentifier(idenname,&idennamelen)) {
					index_tmp = searchSym(idenname, idennamelen);
					if (index_tmp != -1) {
						//@
						interPrintSCANFCUR(cursymtable->sym[index_tmp].type, cursymtable->sym[index_tmp].offset);
					}
					else {
						index_tmp = searchGlobalSym(idenname, idennamelen);
						if (index_tmp != -1) {
							//@
							interPrintSCANFGLO(idenname, idennamelen, glosymtable->sym[index_tmp].type);
						}
						else {
							//�����ڵı�ʶ��
							err(32);
							__nextCommaOrRightParenthesesOrSemicolon();
						}
					}
				}
				else {
					//need identifier
					err(14);
					__nextCommaOrRightParenthesesOrSemicolon();
				}
			} while (type ==SYMSYM&&value ==',');
			if (type == SYMSYM && value == ')') {
				if(nextsym()==EOF){err(43);}
			}
			else {
				//need )
				err(12);
				__nextSemicolon();
				return;
			}
		}
		else {
			//need (
			err(13);
			__nextSemicolon();
			return;
		}
	}
	else {
		return;//not scanf
	}
}
void isPrintfStatement() {//д���
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("д���\n");
	}
	int exp_type,exp_value,exp_const,exp_counter;
	if (type == RESSYM && value == PRINTF) {
		if(nextsym()==EOF){err(43);}
		if (type == SYMSYM && value == '(') {
			if(nextsym()==EOF){err(43);}
			if (type == STRSYM) {
				isString();
				if (type == SYMSYM && value == ',') {
					interPrintPRINTFSPACE();
					if(nextsym()==EOF){err(43);}
					if (!isExpression(&exp_type,&exp_const,&exp_value,&exp_counter)) {
						__nextSemicolon();
						return;
					}
					if (type == SYMSYM && value == ')') {
						interPrintPRINTFEXP(exp_type,exp_const,exp_value,exp_counter);
						if (!exp_const) {
							releaseRegCounter(exp_counter);
						}
						interPrintPRINTFENTER();
						if(nextsym()==EOF){err(43);}
					}
					else {
						//need )
						err(12);
						__nextSemicolon();
						return;
					}
				}
				else if (type == SYMSYM && value == ')') {
					interPrintPRINTFENTER();
					if(nextsym()==EOF){err(43);}
				}
				else {
					//need ,/)
					err(24);
					__nextSemicolon();
					return;
				}
			}
			else {
				if (!isExpression(&exp_type, &exp_const, &exp_value, &exp_counter)) {
					__nextSemicolon();
					return;
				}
				if (type == SYMSYM && value == ')') {
					interPrintPRINTFEXP(exp_type, exp_const, exp_value, exp_counter);
					interPrintPRINTFENTER();
					if(nextsym()==EOF){err(43);}
				}
				else {
					//need )
					err(12);
					__nextSemicolon();
					return;
				}
			}
		}
		else {
			//need (
			err(13);
			__nextSemicolon();
			return;
		}
	}
	else {
		return;//not printf statement
	}
}
void isReturnStatement() {//�������
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("�������\n");
	}
	int exp_type,exp_const,exp_value,exp_counter;
	if (type == RESSYM && value == RETURN) {
		if(nextsym()==EOF){err(43);}
		if (type == SYMSYM && value == '(') {
			if(nextsym()==EOF){err(43);}
			if (!isExpression(&exp_type,&exp_const,&exp_value,&exp_counter)) {
				__nextSemicolon();
				return;
			}
			if (type == SYMSYM && value == ')') {
				if(nextsym()==EOF){err(43);}
			}
			else {
				//need )
				err(12);
				__nextSemicolon();
				return;
			}
			interPrintStoreReturnValue(exp_const,exp_value,exp_counter);
			if (!exp_const) {
				releaseRegCounter(exp_counter);
			}
		}
		interPrintRETURN();
	}
	else {
		return;//not return statement
	}
}
void isAddOperator(int *addflag) {//�ӷ������
	if (type == ADDSYM) {
		if (value == '+') {
			*addflag = 1;
		}
		else {
			*addflag = -1;
		}
		if(nextsym()==EOF){err(43);}
		return;
	}
	else {
		*addflag = 1;
		return;//not add operator
	}
}
void isMulOperator(int *mulflag) {//�˷������
	if (type == MULSYM) {
		if (value == '*') {
			*mulflag = 1;
		}
		else {
			*mulflag = 0;
		}
		if(nextsym()==EOF){err(43);}
		return;
	}
	else {
		*mulflag = 1;
		return;//not mul operator
	}
}
int isRelationOperator(int *ope) {//��ϵ�����
	if (type == RELSYM) {
		*ope = value;
		if(nextsym()==EOF){err(43);}
		return 1;
	}
	else {
		//not relation operator
		return 0;
	}
}
int isChar(int *symvalue) {//�ַ�
	if (type == CHASYM) {
		*symvalue = value;
		if(nextsym()==EOF){err(43);}
		return 1;
	}
	else {
		return 0;//not char
	}
}
int isString() {//�ַ���
	if (type == STRSYM) {
		interPrintPRINTFSTR(string, value);
		if(nextsym()==EOF){err(43);}
		return 1;
	}
	else {
		return 0;//not string
	}
}
int isConst(int *value_tmp,int *type_tmp) {//����//todo
	
	if (isChar(value_tmp)) {
		*type_tmp = CHAR;
		return 1;
	}
	else if (isInteger(value_tmp)) {
		*type_tmp = INT;
		return 1;
	}
	else {
		return 0;
	}
}
int isInteger(int *symvalue) {//����
	if (type == ADDSYM) {
		if (value == '-') {
			if(nextsym()==EOF){err(43);}
			if (!isUnsignedInteger(symvalue)) {
				return 0;
			}
			*symvalue = (-1)*(*symvalue);
		}
		else {//value == '+'
			if(nextsym()==EOF){err(43);}
			if (!isUnsignedInteger(symvalue)) {
				return 0;
			}
		}
		return 1;
	}
	else {
		if (!isUnsignedInteger(symvalue)) {
			return 0;
		}
		return 1;
	}
}
int isUnsignedInteger(int *symvalue) {//�޷�������
	if (type == UNISYM) {
		*symvalue = value;
		if(nextsym()==EOF){err(43);}
		return 1;
	}
	else {
		return 0;//not unsigned integer
	}
}
void isMain() {//�������Ӿ�
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("����������main\n");
	}
	insertFun("main", 4, VOID);
	if (type == RESSYM && value == MAIN) {
		if(nextsym()==EOF){err(43);}
		if (type == SYMSYM && value == '(') {
			interPrintFUNDEF("main", 4);
			if(nextsym()==EOF){err(43);}
			if (type == SYMSYM && value == ')') {
				if(nextsym()==EOF){err(43);}
				if (type == SYMSYM && value == '{') {
					if(nextsym()==EOF){err(43);}
					isCompoundStatement();
					if (type == SYMSYM && value == '}') {
						if (nextsym() == EOF) {
							interPrintRETURN();
							/*interPrintFUNEND();*/
						}
						else {
							//err too much syms
							err(42);
							return;
						}
					}
					else {
						//need }
						err(10);
						return;
					}
				}
				else {
					//need {
					err(11);
					return;
				}
			}
			else {
				//need )
				err(12);
				return;
			}
		}
		else {
			//need (
			err(13);
			return;
		}
	}
	else {
		//need main
		err(18);
		return;
	}
}
int isExpression(int *exp_type,int *exp_const,int *exp_value,int *counter) {//���ʽ
	int addflag;
	int type_tmp,cst_tmp,value_tmp,counter_tmp;
	isAddOperator(&addflag);
	if (!isTerm(exp_type,exp_const,exp_value,counter)) {
		err(33);
		return 0;
	}
	if (*exp_const) {
		*exp_value *= addflag;
	}
	else {
		interPrintMinusCounter(counter,addflag);
	}
	if (type != ADDSYM) {
		//�˱��ʽ���������һ��register
		return 1;
	}
	while (type == ADDSYM) {
		isAddOperator(&addflag);
		if (!isTerm(&type_tmp,&cst_tmp,&value_tmp,&counter_tmp)) {
			err(33);
			return 0;
		}
		*exp_type = INT;
		/**exp_const *= cst_tmp;*/
		if (!*exp_const) {
			if (!cst_tmp) {
				if (*counter < counter_tmp) {
					interPrintExpNDND(*counter, counter_tmp, addflag);
					releaseRegCounter(counter_tmp);
				}
				else {
					interPrintExpNDND(counter_tmp, *counter, addflag);
					releaseRegCounter(*counter);
					*counter = counter_tmp;
				}
			}
			else {
				interPrintExpDND(*counter, value_tmp, addflag, 2);
			}
		}
		else if(!cst_tmp){
			interPrintExpDND(counter_tmp,*exp_value,addflag, 1);
			*exp_const = 0;
			*counter = counter_tmp;
		}
		else {
			*exp_value += value_tmp * addflag;
		}
	}
	return 1;
}
int isTerm(int *ter_type,int *ter_const, int *ter_value,int *counter) {//��
	int mulflag;
	int type_tmp, cst_tmp, value_tmp,counter_tmp;
	if (!isDivisor(ter_type,ter_const,ter_value,counter)) {
		return 0;
	}
	if (type != MULSYM) {
		//��������ӹ���һ��register
		return 1;
	}
	while (type == MULSYM) {
		isMulOperator(&mulflag);
		if (!isDivisor(&type_tmp,&cst_tmp,&value_tmp,&counter_tmp)) {
			return 0;
		}
		*ter_type = INT;
		/**ter_const *= cst_tmp;*/
		if (!*ter_const) {
			if (!cst_tmp) {
				if (*counter < counter_tmp) {
					interPrintTrmNDND(*counter,counter_tmp,mulflag);
					releaseRegCounter(counter_tmp);
				}
				else {
					interPrintTrmNDND(counter_tmp, *counter, mulflag);
					releaseRegCounter(*counter);
					*counter = counter_tmp;
				}
				
			}
			else {
				interPrintTrmDND(*counter,value_tmp,mulflag, 2);
			}
		}
		else if (!cst_tmp) {
			interPrintTrmDND(counter_tmp,*ter_value,mulflag, 1);
			*ter_const = 0;
			*counter = counter_tmp;
		}
		else {
			if (mulflag/*'*'*/) {
				*ter_value *= value_tmp;
			}
			else {
				*ter_value /= value_tmp;
			}
		}
	}
	return 1;
}
int isDivisor(int *dvs_type, int *dvs_const, int *dvs_value,int *counter) {//����
	/*int type_tmp, cst_tmp, value_tmp,counter_tmp;*/
	int index;
	if (type == IDESYM) {
		char dvsname[IDE_MAX_LEN];
		int dvsnamelen;
		isIdentifier(dvsname,&dvsnamelen);
		if (type == SYMSYM && value == '(') {
			if (isUseFunWithValue(dvsname,dvsnamelen,dvs_type)) {
				*dvs_const = 0;
				getTmpRegisters();
				*counter = newRegCounter();
				interPrintRTRVLE(*counter);
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (type == SYMSYM && value == '[') {
			int upbound_tmp,global_flag;
			
			index = searchSym(dvsname, dvsnamelen);
			if (index!= -1&& cursymtable->sym[index].array==ARR) {
				*dvs_type = cursymtable->sym[index].type;
				*dvs_const = 0;
				upbound_tmp = cursymtable->sym[index].upbound;
				global_flag = 0;
			}
			else {
				index = searchGlobalSym(dvsname, dvsnamelen);
				if (index != -1 && glosymtable->sym[index].array == ARR) {
					*dvs_type = glosymtable->sym[index].type;
					*dvs_const = 0;
					upbound_tmp = glosymtable->sym[index].upbound;
					global_flag = 1;
				}
				else {//�����ڷ���
					//err using of a identifier without declaration

					err(32);
					return 0;
				}
			}
			int index_type,index_const,index_value,index_counter;
			if(nextsym()==EOF){err(43);}
			if (!isExpression(&index_type,&index_const,&index_value,&index_counter)) {
				return 0;
			}
			if (index_type == CHAR) {
				//err expect an int expression here
				err(34);
				return 0;
			}
			if (index_const) {
				if (index_value >= upbound_tmp || index_value < 0) {
					//err invalid index value
					err(35);
					return 0;
				}
				*counter = newRegCounter();
				//@����valueȡ����ֵ�������µ�t
				if (global_flag) {
					int offset = index_value * (glosymtable->sym[index].type == INT ? 4 : 1);
					interPrintGLOARRACC1(*counter,dvsname,dvsnamelen, glosymtable->sym[index].type,offset);
				}
				else {
					int offset = index_value * (cursymtable->sym[index].type == INT ? 4 : 1) + cursymtable->sym[index].offset;
					interPrintCURARRACC1(*counter, cursymtable->sym[index].type,offset);
				}
			}
			else {
				if (global_flag) {
					interPrintGLOARRACC2(index_counter, dvsname, dvsnamelen, glosymtable->sym[index].type, index_counter);
				}
				else {
					int offset = cursymtable->sym[index].offset;
					interPrintCURARRACC2(index_counter, cursymtable->sym[index].type, index_counter, offset);
				}

				*counter = index_counter;
				//@����expression��t(index_counter)ȡ������ֵ�����µ�t
			}
			if (type == SYMSYM && value == ']') {
				if(nextsym()==EOF){err(43);}
				return 1;
			}
			else {
				//need ]
				err(9);
				return 0;
			}
		}
		else {
			//is divisor in table?
			index = searchSym(dvsname, dvsnamelen);
			if (index != -1&& cursymtable->sym[index].array == NOTARR) {
				*dvs_type = cursymtable->sym[index].type;
				*dvs_const = cursymtable->sym[index].definite;
				*dvs_value = cursymtable->sym[index].value;
				//���þֲ�����������ȷ���Ծ����Ƿ������µ�t
				if (!*dvs_const) {
					*counter = newRegCounter();
					interPrintCURVARACC(*counter, *dvs_type, cursymtable->sym[index].offset);
				}
			}
			else {
				index = searchGlobalSym(dvsname, dvsnamelen);
				if (index != -1 && glosymtable->sym[index].array == NOTARR) {
					*dvs_type = glosymtable->sym[index].type;
					*dvs_const = glosymtable->sym[index].definite;
					*dvs_value = glosymtable->sym[index].value;
					//����ȫ�ֱ���������ȷ���Ծ����Ƿ������µ�t
					if (!*dvs_const) {
						*counter = newRegCounter();
						interPrintGLOVARACC(*counter, dvsname, dvsnamelen, *dvs_type);
					}
				}
				else {//�����ڷ���
				//err using of a identifier without declaration
					err(32);
					return 0;

				}
			}
			return 1;
		}
	}
	else if (type == SYMSYM && value == '(') {
		if(nextsym()==EOF){err(43);}
		if (!isExpression(dvs_type,dvs_const,dvs_value,counter)) {
			return 0;
		}
		if (type == SYMSYM && value == ')') {
			if(nextsym()==EOF){err(43);}
			*dvs_type = INT;
			return 1;
		}
		else {
			//need )
			err(12);
			return 0;
		}
	}
	else if (isInteger(dvs_value)) {
		*dvs_type = INT;
		*dvs_const = 1;
	}
	else if (isChar(dvs_value)) {
		*dvs_type = CHAR;
		*dvs_const = 1;
	}
	else {
		//need divisor
		err(19);
		return 0;
	}
	return 1;
}
void isGlobalVariableDeclare() {//ȫ�ֱ�������
	char idenname[IDE_MAX_LEN];
	int idennamelen,identype,idenupbound=0;
	int arr;
	while (type == RESSYM && (value == INT || value == CHAR)) {
		arr = NOTARR;
		identype = value;
		if(nextsym()==EOF){err(43);}
		isIdentifier(idenname,&idennamelen);
		if (type == SYMSYM && value == '(') {
			if(nextsym()==EOF){err(43);}
			interPrintGLOVAR();
			isDefFunWithValueSon(idenname,idennamelen,identype);
			return;
		}
		else {
			if (gramma_debug) {
				printf("%d:", line_number);
				printf("�����������\n");
			}
			do {
				if (type == SYMSYM && value == '[') {
					if(nextsym()==EOF){err(43);}
					if (!isUnsignedInteger(&idenupbound)) {
						//need unsigned int
						err(26);
						__nextCommaOrSemicolon();
					}
					else {
						if (type == SYMSYM && value == ']') {
							if(nextsym()==EOF){err(43);}
						}
						else {
							//need ]
							err(9);
							__nextCommaOrSemicolon();
						}
					}
					arr = ARR;
					
					/*addSym(idenname,idennamelen,VARIABLE,identype,ARR,idenupbound,ZERO,0);*/
				}
				else if (type == SYMSYM && value == ',') {
					//��ɱ�������¼��
					addSym(idenname, idennamelen, VARIABLE, identype, arr, idenupbound, ZERO,0);
					arr = NOTARR;
					idenupbound = 0;
					if(nextsym()==EOF){err(43);}
					isIdentifier(idenname,&idennamelen);//�ٶ���һ��
				}
				else if (type == SYMSYM && value == ';') {
					//��ɱ�������¼��	
				}
				else {
					//need ,;[
					err(25);
					__nextCommaOrSemicolon();
				}	
			} while (type == SYMSYM && (value == ',' || value == '['));
			if (type == SYMSYM && value == ';') {
				addSym(idenname, idennamelen, VARIABLE, identype, arr, idenupbound, ZERO, 0);
				if(nextsym()==EOF){err(43);}
			}
			else {
				//need ;
				err(5);
				__nextSemicolon();
			}
		}
	}
	interPrintGLOVAR();
	return;
}
void isDefFunWithValueSon(char *funname,int funnamelen,int funtype) {//�з���ֵ���������Ӿ�
	if (gramma_debug) {
		printf("%d:", line_number);
		printf("�з���ֵ��������\n");
	}
	resetRegPool();
	insertFun(funname, funnamelen, funtype);
	interPrintFUNDEF(funname, funnamelen);
	if (!isParameterTable()) {
		__nextReservedSymbol();
		return;
	}
	if (type == SYMSYM && value == ')') {
		if(nextsym()==EOF){err(43);}
		if (type == SYMSYM && value == '{') {
			if(nextsym()==EOF){err(43);}
			isCompoundStatement();
			if (type == SYMSYM && value == '}') {
				//@
				if(nextsym()==EOF){err(43);}
				interPrintRETURN();
				/*interPrintFUNEND();*/
			}
			else {
				//err need}
				err(10);
				__nextReservedSymbol();
				return;
			}
		}
		else {
			//err need{
			err(11);
			__nextReservedSymbol();
			return;
		}
	}
	else {
		//err need��
		err(12);
		__nextReservedSymbol();
		return;
	}
}
void isProgram() {//����
	interPrintGLOCSTSTART();
	isGlobalConstDeclare();
	interPrintGLOCSTEND();
	isGlobalVariableDeclare();

	if (type == RESSYM) {
		while (type == RESSYM) {
			if (value == INT || value == CHAR) {
				isDefFunWithValue();
			}
			else if (value == VOID) {
				if(nextsym()==EOF){err(43);}
				if (type == IDESYM) {
					isDefFunWithoutValue();
				}
				else if (type == RESSYM && value == MAIN) {
					isMain();
					break;
				}
				else {
					//wrong symbol
					err(20);
				}
			}
			else {
				//worng resserved symbol
				err(7);
			}
		}
	}
	else {
		//need resserved symbol//ʵ������ȱ��main�����ı���
		err(21);
	}
}
