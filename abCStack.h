/* 
    abCStack.h
        By: Jeremy Rand
 */


#ifndef ABCSTACK_H
#define ABCSTACK_H


#include "expr/abCExpr.h"


#define AB_CALC_STACK_DEPTH 128


void abCalcStackInit(void);

abCalcExpr *abCalcStackExprPush(abCalcExpr *expr);

abCalcExpr *abCalcStackExprPop(abCalcExpr *expr);

abCalcExpr *abCalcStackExprAt(int depth);

char *abCalcStackExprStringAt(int depth, char *buffer);

int abCalcStackNumItems(void);

void abCalcStackClear(void);


#endif
