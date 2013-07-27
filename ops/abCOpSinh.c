/* 
    abCOpSinh.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpSinh.h"


#define SINH_NAME "SINH"


static void sinhExecute(void);


void abCalcOpSinhInit(void)
{
    abCalcOpRegister(SINH_NAME, sinhExecute);
}


void sinhExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(SINH_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, SINH_NAME);
        return;
    }

    abCalcExprRealSet(&result, sinh(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
