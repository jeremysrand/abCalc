/* 
    abCStack.h
        By: Jeremy Rand
 */


#ifndef ABCSTACK_H
#define ABCSTACK_H


#include "expr/abCExpr.h"


void abCalcStackInit(void);

abCalcExpr *abCalcStackExprPush(abCalcExpr *expr);

abCalcExpr *abCalcStackExprPop(abCalcExpr *expr);

abCalcExpr *abCalcStackExprAt(int depth);

int abCalcStackNumItems(void);


#endif
