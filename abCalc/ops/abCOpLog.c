/* 
    abCOpLog.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpLog.h"


#define LOG_NAME "LOG"


static void logExecute(void);


void abCalcOpLogInit(void)
{
    abCalcOpRegister(LOG_NAME, logExecute);
}


void logExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(LOG_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, LOG_NAME);
        return;
    }

    if (expr->u.real == 0.0) {
        abCalcRaiseError(abCalcInfiniteResultError, LOG_NAME);
        return;
    }
    if (expr->u.real < 0.0) {
        abCalcRaiseError(abCalcComplexResultError, LOG_NAME);
        return;
    }

    abCalcExprRealSet(&result, log10(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
