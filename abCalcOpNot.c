/* 
    abCalcOpNot.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpNot.h"

#include "abCalcOp.h"
#include "abCalcError.h"
#include "abCalcExpr.h"
#include "abCalcExprInt.h"
#include "abCalcStack.h"


#define OP_NAME "NOT"


static void notExecute(void);


void abCalcOpNotInit(void)
{
    abCalcOpRegister(OP_NAME, notExecute);
}


void notExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(OP_NAME);

    if (expr->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, OP_NAME);
        return;
    }

    abCalcExprIntSet(&result, ~(expr->u.integer));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
