#pragma once
#ifndef ICgen_H
#define ICgen_H

#include <stdio.h>
#include <string.h>
#include "macrodef.h"
#include "symtable.h"
#include "translate.h"





extern char inter_file[MAX_FILE_LEN];
extern char inter_file2[MAX_FILE_LEN];
extern FILE *fp_inter;
extern FILE *fp_inter2;
extern int inter_debug;

void interPrintStart();
void interPrintEnd();
void intercpy();

int newRegCounter();
void resetRegPool();
void releaseRegCounter(int i);
void saveTmpRegisters();
void getTmpRegisters();

void resetCaseCounter();


//void interPrintString(char*);
//void interPrintLabel(int);

void interPrintGLOCST(char *name, int namelen, int type, int value);
void interPrintFUNCST(int type, int value, int offset);
void interPrintGLOVAR();
void interPrintFUNDEF(char *funname, int funnamelen);
void interPrintFUNEND();
void interPrintExpNDND(int para1, int para2, int addflag);
void interPrintExpDND(int para1, int const2, int addflag, int whoisconst);
void interPrintTrmNDND(int para1, int para2, int mulflag);
void interPrintTrmDND(int para1, int para2, int mulflag, int whoisconst);
void interPrintRTRVLE(int counter);
void interPrintGLOARRACC1(int counter, char *name, int namelen, int type, int offset);
void interPrintCURARRACC1(int counter, int type, int offset);
void interPrintGLOARRACC2(int counter, char *name, int namelen, int type, int counter2);
void interPrintCURARRACC2(int counter, int type, int counter2, int offsetofarray);
void interPrintGLOVARACC(int counter, char *name, int namelen, int type);
void interPrintCURVARACC(int counter, int type, int offset);

void interPrintStoreReturnValue(int v_const, int v_value, int v_counter);
void interPrintRETURN();
void interPrintPRINTFSTR(char *str, int strlen);
void interPrintPRINTFEXP(int exp_type, int exp_const, int exp_value, int exp_counter);
void interPrintPRINTFENTER();
void interPrintPRINTFSPACE();
void interPrintSCANFCUR(int identype, int offset);
void interPrintSCANFGLO(char *idenname, int idennamelen, int identype);

void interPrintASSGLOCST(char *idenname, int idennamelen, int identype, int idenvalue);
void interPrintASSGLOVAR(char *idenname, int idennamelen, int identype, int idencounter);
void interPrintASSCURCST(int identype, int idenoffset, int idenvalue);
void interPrintASSCURVAR(int identype, int idenoffset, int idencounter);
void interPrintASSARR(int global_flag, char *idenname, int idennamelen, int identype, int idenoffset,
	int leftconst, int leftvalue, int leftcounter,
	int idenconst, int idenvalue, int idencounter);

void interPrintWhileStart(int *while_index);
void interPrintBackWhile(int while_index);
void interPrintWhileEnd(int while_index);
void interPrintIfStart(int *if_index);
void interPrintIfEnd(int if_index);
void interPrintJudge1(int judgetype, int judge_index,
	int exp1_const, int exp1_value, int exp1_counter);

void interPrintJudge2(int judgetype, int judge_index, int operatorType,
	int exp1_const, int exp1_value, int exp1_counter,
	int exp2_const, int exp2_value, int exp2_counter);


void interPrintSwitchStart(int *switch_index);
void interPrintSwitchEnd(int switch_index);
void interPrintDefault(switch_index);
void interPrintGetCase(int *case_index);
void interPrintCaseJudge(int case_index, int switch_index,
	int const_value, int const_type,
	int exp_type, int exp_const, int exp_value, int exp_counter);
void interPrintCaseEnd(int case_index, int switch_index);
void interPrintGotoSwitchEnd(int switch_index);

void interPrintFUNUSE(char *funname, int funnamelen, int funsize);
void interPrintFUNJMP(char *funname, int funnamelen);
void interPrintPara(int para_offset, int exp_type, int exp_const, int exp_value, int exp_counter);

void interPrintMinusCounter(int *counter, int addflag);

void interPrintGLOCSTSTART();
void interPrintGLOCSTEND();

void interPrintFUNSAVE();
#endif