/* 
    abCOpB2R.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"
#include "expr/abCExprInt.h"

#include "ops/abCOp.h"
#include "ops/abCOpB2R.h"


#define B2R_NAME "B2R"


static void b2rExecute(void);


void abCalcOpB2RInit(void)
{
    abCalcOpRegister(B2R_NAME, b2rExecute);
}


void b2rExecute(void)
{
    abCalcExpr result;
    int width;
    int topBit;
    AB_CALC_OP_ONE_ARG(B2R_NAME);

    if (expr->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, B2R_NAME);
        return;
    }

    abCalcExprRealSet(&result, (abCalcRealType)expr->u.integer);

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
