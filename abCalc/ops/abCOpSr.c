/* 
    abCOpSr.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExprInt.h"

#include "ops/abCOp.h"
#include "ops/abCOpSr.h"


#define SR_NAME "SR"


static void srExecute(void);


void abCalcOpSrInit(void)
{
    abCalcOpRegister(SR_NAME, srExecute);
}


void srExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(SR_NAME);

    if (expr->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, SR_NAME);
        return;
    }

    abCalcExprIntSet(&result, (expr->u.integer >> 1));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
