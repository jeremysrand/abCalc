/* 
    abCOpAtanh.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpAtanh.h"


#define ATANH_NAME "ATANH"


static void atanhExecute(void);


void abCalcOpAtanhInit(void)
{
    abCalcOpRegister(ATANH_NAME, atanhExecute);
}


void atanhExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(ATANH_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, ATANH_NAME);
        return;
    }

    if ((expr->u.real == 1.0) ||
        (expr->u.real == -1.0)) {
        abCalcRaiseError(abCalcInfiniteResultError, ATANH_NAME);
        return;
    }
    if ((expr->u.real > 1.0) ||
        (expr->u.real < -1.0)) {
        abCalcRaiseError(abCalcComplexResultError, ATANH_NAME);
        return;
    }

    abCalcExprRealSet(&result, atanh(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
