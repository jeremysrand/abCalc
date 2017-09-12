/* 
    abCOpLn.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpLn.h"


#define LN_NAME "LN"


static void lnExecute(void);


void abCalcOpLnInit(void)
{
    abCalcOpRegister(LN_NAME, lnExecute);
}


void lnExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(LN_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, LN_NAME);
        return;
    }

    if (expr->u.real == 0.0) {
        abCalcRaiseError(abCalcInfiniteResultError, LN_NAME);
        return;
    }
    if (expr->u.real < 0.0) {
        abCalcRaiseError(abCalcComplexResultError, LN_NAME);
        return;
    }

    abCalcExprRealSet(&result, log(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
