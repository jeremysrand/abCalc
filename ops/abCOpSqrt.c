/* 
    abCOpSqrt.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpSqrt.h"


#define SQRT_NAME "SQRT"


static void sqrtExecute(void);


void abCalcOpSqrtInit(void)
{
    abCalcOpRegister(SQRT_NAME, sqrtExecute);
}


void sqrtExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(SQRT_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, SQRT_NAME);
        return;
    }

    abCalcExprRealSet(&result, sqrt(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
