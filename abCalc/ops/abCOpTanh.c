/* 
    abCOpTanh.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpTanh.h"


#define TANH_NAME "TANH"


static void tanhExecute(void);


void abCalcOpTanhInit(void)
{
    abCalcOpRegister(TANH_NAME, tanhExecute);
}


void tanhExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(TANH_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, TANH_NAME);
        return;
    }

    abCalcExprRealSet(&result, tanh(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
