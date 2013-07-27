/* 
    abCOpNot.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExprInt.h"

#include "ops/abCOp.h"
#include "ops/abCOpNot.h"


#define NOT_NAME "NOT"


static void notExecute(void);


void abCalcOpNotInit(void)
{
    abCalcOpRegister(NOT_NAME, notExecute);
}


void notExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(NOT_NAME);

    if (expr->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, NOT_NAME);
        return;
    }

    abCalcExprIntSet(&result, ~(expr->u.integer));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
