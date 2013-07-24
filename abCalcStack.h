/* 
    abCalcStack.h
        By: Jeremy Rand
 */


#include "abCalcExpr.h"

void abCalcStackInit(void);

abCalcExpr *abCalcStackExprPush(abCalcExpr *expr);

abCalcExpr *abCalcStackExprPop(abCalcExpr *expr);

abCalcExpr *abCalcStackExprAt(abCalcExpr *expr, int depth);
