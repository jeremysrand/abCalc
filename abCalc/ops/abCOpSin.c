/* 
    abCOpSin.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpSin.h"


#define SIN_NAME "SIN"


static void sinExecute(void);


void abCalcOpSinInit(void)
{
    abCalcOpRegister(SIN_NAME, sinExecute);
}


void sinExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(SIN_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, SIN_NAME);
        return;
    }

    abCalcExprRealSet(&result, sin(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
