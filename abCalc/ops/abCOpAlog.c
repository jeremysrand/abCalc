/* 
    abCOpAlog.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpAlog.h"


#define ALOG_NAME "ALOG"


static void alogExecute(void);


void abCalcOpAlogInit(void)
{
    abCalcOpRegister(ALOG_NAME, alogExecute);
}


void alogExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(ALOG_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, ALOG_NAME);
        return;
    }

    abCalcExprRealSet(&result, pow(10.0, expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
