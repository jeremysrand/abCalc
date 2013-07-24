/* 
    abCalcStack.h
        By: Jeremy Rand
 */


#ifndef ABCALCSTACK_H
#define ABCALCSTACK_H


#include "abCalcExpr.h"

void abCalcStackInit(void);

abCalcExpr *abCalcStackExprPush(abCalcExpr *expr);

abCalcExpr *abCalcStackExprPop(abCalcExpr *expr);

abCalcExpr *abCalcStackExprAt(abCalcExpr *expr, int depth);

int abCalcStackNumItems(void);


#endif
