/* 
    abCOpCos.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpCos.h"


#define COS_NAME "COS"


static void cosExecute(void);


void abCalcOpCosInit(void)
{
    abCalcOpRegister(COS_NAME, cosExecute);
}


void cosExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(COS_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, COS_NAME);
        return;
    }

    abCalcExprRealSet(&result, cos(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
