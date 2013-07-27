/* 
    abCOpLnp1.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpLnp1.h"


#define LNP1_NAME "LNP1"


static void lnp1Execute(void);


void abCalcOpLnp1Init(void)
{
    abCalcOpRegister(LNP1_NAME, lnp1Execute);
}


void lnp1Execute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(LNP1_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, LNP1_NAME);
        return;
    }

    if (expr->u.real == -1.0) {
        abCalcRaiseError(abCalcInfiniteResultError, LNP1_NAME);
        return;
    }
    if (expr->u.real < -1.0) {
        abCalcRaiseError(abCalcComplexResultError, LNP1_NAME);
        return;
    }

    abCalcExprRealSet(&result, log1p(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
