/* 
    abCOpExp.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpExp.h"


#define EXP_NAME "EXP"


static void expExecute(void);


void abCalcOpExpInit(void)
{
    abCalcOpRegister(EXP_NAME, expExecute);
}


void expExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(EXP_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, EXP_NAME);
        return;
    }

    abCalcExprRealSet(&result, exp(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
