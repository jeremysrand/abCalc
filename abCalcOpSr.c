/* 
    abCalcOpSr.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpSr.h"

#include "abCalcOp.h"
#include "abCalcError.h"
#include "abCalcExpr.h"
#include "abCalcExprInt.h"
#include "abCalcStack.h"


#define OP_NAME "SR"


static void srExecute(void);


void abCalcOpSrInit(void)
{
    abCalcOpRegister(OP_NAME, srExecute);
}


void srExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(OP_NAME);

    if (expr->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, OP_NAME);
        return;
    }

    abCalcExprIntSet(&result, (expr->u.integer >> 1));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
