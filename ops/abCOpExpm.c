/* 
    abCOpExpm.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpExpm.h"


#define EXPM_NAME "EXPM"


static void expmExecute(void);


void abCalcOpExpmInit(void)
{
    abCalcOpRegister(EXPM_NAME, expmExecute);
}


void expmExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(EXPM_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, EXPM_NAME);
        return;
    }

    abCalcExprRealSet(&result, expm1(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
