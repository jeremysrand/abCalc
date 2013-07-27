/* 
    abCOpAcosh.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpAcosh.h"


#define ACOSH_NAME "ACOSH"


static void acoshExecute(void);


void abCalcOpAcoshInit(void)
{
    abCalcOpRegister(ACOSH_NAME, acoshExecute);
}


void acoshExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(ACOSH_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, ACOSH_NAME);
        return;
    }

    if (expr->u.real < 1.0) {
        abCalcRaiseError(abCalcComplexResultError, ACOSH_NAME);
        return;
    }

    abCalcExprRealSet(&result, acosh(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
