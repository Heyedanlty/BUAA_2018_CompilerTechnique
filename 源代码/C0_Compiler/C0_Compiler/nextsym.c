#include "nextsym.h"

char buffer[LIN_MAX_LEN];	//ȫ���ַ�
char iden[IDE_MAX_LEN];		//��ʶ������
char string[STR_MAX_LEN];	//�ַ�������
int type;					//�洢��ȡ�����һ��������
int value;					//�洢��ȡ�����һ����ֵ
FILE *fp_read;				//���ļ�ָ��
int flag_read = 1;			//�ж�ȡ���ʶ��0û����1���꣩
int lp = 0;					//��ָ�루line_pointer),ָʾ����һ���������� �ַ� 
int last_lp = 0;			//��һ����ָ�룬���ڳ�����ʹ��
char read_file[MAX_FILE_LEN];
int line_number = 0;

int nextsym_debug = 0;

int nextsym()
{
	while (flag_read) {//�����Ҫ�����µ�һ��
		if (fgets(buffer, LIN_MAX_LEN, fp_read) == NULL) {//����Ѿ�û������Ҫ���˵Ļ�
			return EOF;//����EOF��-1��
		}
		line_number++;
		lp = 0;
		while (buffer[lp] == ' ' || buffer[lp] == '\t') {
			lp++;
		}
		if (buffer[lp] != '\n'&&buffer[lp] != '\0') {//������в��ǿ��еĻ�
			flag_read = 0;//������������ѭ��
		}
	}

	//printf("'%c' : ", buffer[lp]);
	switch (buffer[lp]) {
	case '+': type = 0;
		value = '+';
		break;
	case '-': type = 0;
		value = '-';
		break;
	case '*': type = 1;
		value = '*';
		break;
	case '/': type = 1;
		value = '/';
		break;
	case '<': type = 2;
		if (buffer[lp + 1] == '=') {
			value = 1;
			lp++;
		}
		else {
			value = 0;
		}
		break;
	case'>': type = 2;
		if (buffer[lp + 1] == '=') {
			value = 3;
			lp++;
		}
		else {
			value = 2;
		}
		break;
	case '!':
		if (buffer[lp + 1] == '=') {
			type = 2;
			value = 4;
			lp++;
		}
		else {
			type = 8;
			value = '!';
		}
		break;
	case'=':
		if (buffer[lp + 1] == '=') {
			type = 2;
			value = 5;
			lp++;
		}
		else {
			type = 7;
			value = '=';
		}
		break;
	case'(': type = 7;
		value = '(';
		break;
	case ')': type = 7;
		value = ')';
		break;
	case'[': type = 7;
		value = '[';
		break;
	case ']': type = 7;
		value = ']';
		break;
	case '{': type = 7;
		value = '{';
		break;
	case '}': type = 7;
		value = '}';
		break;
	case ';': type = 7;
		value = ';';
		break;
	case ':': type = 7;
		value = ':';
		break;
	case ',': type = 7;
		value = ',';
		break;
	case '"': str_judge();
		break;
	case '\'': chr_judge();
		break;
	default: judge();
	}
	lp++;//��ʱlp��Ϊ��һ��δ�����ַ�
	while (buffer[lp] == ' ' || buffer[lp] == '\t') {
		lp++;
	}
	if (buffer[lp] == '\n'||buffer[lp]=='\0') {
		flag_read = 1;
	}
	return 1;
}

void judge() {
	if (isnum(buffer[lp])) {
		num_judge();
	}
	else if (islet(buffer[lp])) {
		if (rsv_judge()) {
			return;
		}
		else {
			iden_judge();
		}
	}
	else {
		type = 9;
		value = -1;
		err(1);
	}
	return;
}

void str_judge() {
	int i = 0;
	memset(string, 0, sizeof(string));
	last_lp = lp;
	while (buffer[lp + 1] != '\n'&&buffer[lp + 1] != '"') {
		if (buffer[lp + 1] == 32 || buffer[lp + 1] == 33 || buffer[lp + 1] >= 35 || buffer[lp + 1] <= 126) {
			string[i] = buffer[lp + 1];
			i++;
			lp++;
		}
		else {
			//�����ַ����ڴ��ڷǷ��ַ�
			err(2);
		}
	}
	if (buffer[lp + 1] == '\n') {//û���ҵ���һ��"�������ַ���
		err(3);
		//��������û���ҵ���һ��˫���ţ���ʱlpΪ�������һ���ַ�������\n)
	}
	lp++;//��ʱlpΪ˫����
	type = 6;
	value = i;
	return;
}

void chr_judge() {
	char c = buffer[lp + 1];
	if (buffer[lp + 2] == '\'') {
		if (c == '+' || c == '-' || c == '*' || c == '/' || isnum(c) || islet(c)) {
			type = 8;
			value = c;
			lp += 2;
			return;
		}
		else {
			//�ַ��Ͳ�����Ҫ����
			err(4);
			return;
		}
	}
	//δ�ҵ�'
	return;
}

void num_judge() {
	int tmp_v = 0;
	if (buffer[lp] == '0') {
		type = 3;
		value = 0;
		return;
	}
	else {
		while (isnum(buffer[lp])) {
			tmp_v *= 10;
			tmp_v += buffer[lp] - '0';
			lp++;
		}
		lp--;
		//if (tmp_v > INT_MAX) {
		//	//���ֹ���err
		//}
		type = 3;
		value = tmp_v;
	}
}

int rsv_judge() {
	if (buffer[lp] == 'i'&&buffer[lp + 1] == 'n'&&buffer[lp + 2] == 't' && isnot(buffer[lp + 3])) {
		type = 4;
		value = 0;
		lp += 2;
		return 1;
	}//int
	else if (buffer[lp] == 'c'&&buffer[lp + 1] == 'h'&&buffer[lp + 2] == 'a' &&buffer[lp + 3] == 'r'&&isnot(buffer[lp + 4])) {
		type = 4;
		value = 1;
		lp += 3;
		return 1;
	}//char
	else if (buffer[lp] == 'v'&&buffer[lp + 1] == 'o'&&buffer[lp + 2] == 'i' &&buffer[lp + 3] == 'd'&&isnot(buffer[lp + 4])) {
		type = 4;
		value = 2;
		lp += 3;
		return 1;
	}//void
	else if (buffer[lp] == 'm'&&buffer[lp + 1] == 'a'&&buffer[lp + 2] == 'i' &&buffer[lp + 3] == 'n'&&isnot(buffer[lp + 4])) {
		type = 4;
		value = 3;
		lp += 3;
		return 1;
	}//main
	else if (buffer[lp] == 's'&&buffer[lp + 1] == 'w'&&buffer[lp + 2] == 'i' &&buffer[lp + 3] == 't'&&buffer[lp + 4] == 'c'&&buffer[lp + 5] == 'h'&&isnot(buffer[lp + 6])) {
		type = 4;
		value = 4;
		lp += 5;
		return 1;
	}//switch
	else if (buffer[lp] == 'c'&&buffer[lp + 1] == 'a'&&buffer[lp + 2] == 's' &&buffer[lp + 3] == 'e'&&isnot(buffer[lp + 4])) {
		type = 4;
		value = 5;
		lp += 3;
		return 1;
	}//case
	else if (buffer[lp] == 'd'&&buffer[lp + 1] == 'e'&&buffer[lp + 2] == 'f' &&buffer[lp + 3] == 'a'&&buffer[lp + 4] == 'u'&&buffer[lp + 5] == 'l' &&buffer[lp + 6] == 't'&&isnot(buffer[lp + 7])) {
		type = 4;
		value = 6;
		lp += 6;
		return 1;
	}//default
	else if (buffer[lp] == 'i'&&buffer[lp + 1] == 'f'&& isnot(buffer[lp + 2])) {
		type = 4;
		value = 7;
		lp += 1;
		return 1;
	}//if
	else if (buffer[lp] == 'w'&&buffer[lp + 1] == 'h'&&buffer[lp + 2] == 'i' &&buffer[lp + 3] == 'l'&&buffer[lp + 4] == 'e'&&isnot(buffer[lp + 5])) {
		type = 4;
		value = 8;
		lp += 4;
		return 1;
	}//while
	else if (buffer[lp] == 's'&&buffer[lp + 1] == 'c'&&buffer[lp + 2] == 'a' &&buffer[lp + 3] == 'n'&&buffer[lp + 4] == 'f'&&isnot(buffer[lp + 5])) {
		type = 4;
		value = 9;
		lp += 4;
		return 1;
	}//scanf
	else if (buffer[lp] == 'p'&&buffer[lp + 1] == 'r'&&buffer[lp + 2] == 'i' &&buffer[lp + 3] == 'n'&&buffer[lp + 4] == 't'&&buffer[lp + 5] == 'f'&&isnot(buffer[lp + 6])) {
		type = 4;
		value = 10;
		lp += 5;
		return 1;
	}//printf
	else if (buffer[lp] == 'r'&&buffer[lp + 1] == 'e'&&buffer[lp + 2] == 't' &&buffer[lp + 3] == 'u'&&buffer[lp + 4] == 'r'&&buffer[lp + 5] == 'n'&&isnot(buffer[lp + 6])) {
		type = 4;
		value = 11;
		lp += 5;
		return 1;
	}//return
	else if (buffer[lp] == 'c'&&buffer[lp + 1] == 'o'&&buffer[lp + 2] == 'n' &&buffer[lp + 3] == 's'&&buffer[lp + 4] == 't'&&isnot(buffer[lp + 5])) {
		type = 4;
		value = 12;
		lp += 4;
		return 1;
	}//const
	else {
		return 0;
	}//not reserved word
}

void iden_judge() {
	int i = 0;
	memset(iden, 0, sizeof(iden));
	while (islet(buffer[lp]) || isnum(buffer[lp])) {
		iden[i] = buffer[lp];
		lp++;
		i++;
	}
	lp--;
	type = 5;
	value = i;
	return;
}

int isnot(char c) {
	if ((!isnum(c)) && (!islet(c))) {
		return 1;
	}
	else {
		return 0;
	}
}
int isnum(char c) {
	if (c >= '0'&&c <= '9') {
		return 1;
	}
	else {
		return 0;
	}
}
int islet(char c) {
	if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z') || c == '_') {
		return 1;
	}
	else {
		return 0;
	}
}

void __nextSemicolon() {//�ܹ�һֱ��ֱ����һ���ֺ� ��ʱlp->";"
	while (nextsym() != -1 && (type != SYMSYM || value != (int)";")) {
	}
}

void __nextCommaOrSemicolon() {//�ܹ�һֱ�������Ż��߷ֺ� ��ʱlp->","||";"
	while (nextsym() != -1 && (type != SYMSYM || (value != (int)";"&&value != (int)","))) {;
	}
}

void __nextClosingBraces() {//�ܹ�һֱ��ֱ����һ���ֺ� ��ʱlp->"}"
	while (nextsym() != -1 && (type != SYMSYM || value != (int)"}")) {
	}
}

void __nextReservedSymbol() {//�ܹ�һֱ��ֱ��RESSYM ��ʱlp->RESSYM
	while (nextsym ()!= -1 && type != RESSYM) {
	}
}

void __nextCommaOrRightParenthesesOrSemicolon() {//�ܹ�һֱ�������Ż��������� ��ʱlp->","||")"
	while (nextsym() != -1 && (type != SYMSYM || (value != (int)")"&&value != (int)","&&value!=(int)";"))) {
	}
}