/* 
    abCOpAsin.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpAsin.h"


#define ASIN_NAME "ASIN"


static void asinExecute(void);


void abCalcOpAsinInit(void)
{
    abCalcOpRegister(ASIN_NAME, asinExecute);
}


void asinExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(ASIN_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, ASIN_NAME);
        return;
    }

    if ((expr->u.real < -1.0) ||
        (expr->u.real > 1.0)) {
        abCalcRaiseError(abCalcComplexResultError, ASIN_NAME);
        return;
    }

    abCalcExprRealSet(&result, asin(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
