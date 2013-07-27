/* 
    abCOpInv.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpInv.h"


#define INV_NAME "INV"


static void invExecute(void);


void abCalcOpInvInit(void)
{
    abCalcOpRegister(INV_NAME, invExecute);
}


void invExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(INV_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, INV_NAME);
        return;
    }

    if (expr->u.real == 0.0) {
        abCalcRaiseError(abCalcInfiniteResultError, INV_NAME);
        return;
    }

    abCalcExprRealSet(&result, 1.0 / expr->u.real);

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
