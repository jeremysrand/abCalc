/* 
    abCalcOpAnd.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpAnd.h"

#include "abCalcOp.h"
#include "abCalcError.h"
#include "abCalcExpr.h"
#include "abCalcExprInt.h"
#include "abCalcStack.h"


#define OP_NAME "AND"


static void andExecute(void);


void abCalcOpAndInit(void)
{
    abCalcOpRegister(OP_NAME, andExecute);
}


void andExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_TWO_ARGS(OP_NAME);

    if (expr1->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, OP_NAME);
        return;
    }

    if (expr2->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, OP_NAME);
        return;
    }

    abCalcExprIntSet(&result, expr2->u.integer & expr1->u.integer);

    abCalcStackExprPop(NULL);
    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
