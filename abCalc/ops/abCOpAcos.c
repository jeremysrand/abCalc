/* 
    abCOpAcos.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpAcos.h"


#define ACOS_NAME "ACOS"


static void acosExecute(void);


void abCalcOpAcosInit(void)
{
    abCalcOpRegister(ACOS_NAME, acosExecute);
}


void acosExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(ACOS_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, ACOS_NAME);
        return;
    }

    if ((expr->u.real < -1.0) ||
        (expr->u.real > 1.0)) {
        abCalcRaiseError(abCalcComplexResultError, ACOS_NAME);
        return;
    }

    abCalcExprRealSet(&result, acos(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
