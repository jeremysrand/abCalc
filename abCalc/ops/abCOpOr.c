/* 
    abCOpOr.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExprInt.h"

#include "ops/abCOp.h"
#include "ops/abCOpOr.h"


#define OR_NAME "OR"


static void orExecute(void);


void abCalcOpOrInit(void)
{
    abCalcOpRegister(OR_NAME, orExecute);
}


void orExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_TWO_ARGS(OR_NAME);

    if (expr1->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, OR_NAME);
        return;
    }

    if (expr2->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, OR_NAME);
        return;
    }

    abCalcExprIntSet(&result, expr2->u.integer | expr1->u.integer);

    abCalcStackExprPop(NULL);
    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
