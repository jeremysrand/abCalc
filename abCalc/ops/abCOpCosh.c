/* 
    abCOpCosh.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpCosh.h"


#define COSH_NAME "COSH"


static void coshExecute(void);


void abCalcOpCoshInit(void)
{
    abCalcOpRegister(COSH_NAME, coshExecute);
}


void coshExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(COSH_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, COSH_NAME);
        return;
    }

    abCalcExprRealSet(&result, cosh(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
