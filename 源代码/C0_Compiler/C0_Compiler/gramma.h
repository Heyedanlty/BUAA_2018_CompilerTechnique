#pragma once
#ifndef GRAMMA_H
#define GRAMMA_H

#include<stdio.h>
#include<string.h>
#include "macrodef.h"
#include "nextsym.h"
#include "symtable.h"
#include "ICgen.h"

int isGlobalConstDeclare();
void isGlobalConstDefination();
int isConstDeclare();
void isConstDefination();
void isVariableDeclare();
void isVariableDefination(int symtype);
void isDefFunWithValue();
void isDefFunWithoutValue();
int isDeclareHead();
int isParameterTable();
int isParameter();
int isTypeIdentifier(int *returntype);
int isIdentifier(char *name, int *namelen);
void isCompoundStatement();
void isStatementColumn();
void isStatement();
void isAssignmentStatement(char *leftname, int leftnamelen);
void isIfStatement();
int isCondition(int judge_type, int judge_index);
void isWhileStatement();
void isSwitchStatement();
int isCaseTable(int switch_index, int exp_type, int exp_const, int exp_value, int exp_counter);
int isDefault(int switch_index);
int isCaseStatement(int switch_index, int exp_type, int exp_const, int exp_value, int exp_counter);
int isUseFunWithValue(char *funname, int funnamelen, int *fun_type);
int isUseFun(char *funname, int funnamelen);
int isValueParameterTable(int *paratype, int *paraoffset, int numofpara,char *funname,int funnamelen, int funsize);
void isScanfStatement();
void isPrintfStatement();
void isReturnStatement();
void isAddOperator(int *addflag);
void isMulOperator(int *mulflag);
int isRelationOperator(int *ope);
int isChar(int *symvalue);
int isString();
int isConst(int *value_tmp, int *type_tmp);
int isInteger(int *symvalue);
int isUnsignedInteger(int *symvalue);
void isMain();
int isExpression(int *exp_type, int *exp_const, int *exp_value, int *counter);
int isTerm(int *ter_type, int *ter_const, int *ter_value, int *counter);
int isDivisor(int *dvs_type, int *dvs_const, int *dvs_value, int *counter);
void isGlobalVariableDeclare();
void isDefFunWithValueSon(char *funname, int funnamelen, int funtype);
void isProgram();


extern int gramma_debug;
extern int flag_variable_finish;

#endif