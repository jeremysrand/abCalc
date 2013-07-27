/* 
    abCOpAsinh.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpAsinh.h"


#define ASINH_NAME "ASINH"


static void asinhExecute(void);


void abCalcOpAsinhInit(void)
{
    abCalcOpRegister(ASINH_NAME, asinhExecute);
}


void asinhExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(ASINH_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, ASINH_NAME);
        return;
    }

    abCalcExprRealSet(&result, asinh(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
