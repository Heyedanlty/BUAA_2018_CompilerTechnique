#pragma once
#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <stdio.h>
#include <string.h>
#include "macrodef.h"
#include "ICgen.h"

void finalPrintStart();
void finalPrintEnd();
void finalPrintProceed();
void finalcpy();

extern FILE *fp_int;
#endif