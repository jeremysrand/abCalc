/* 
    abCOpAnd.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExprInt.h"

#include "ops/abCOp.h"
#include "ops/abCOpAnd.h"


#define AND_NAME "AND"


static void andExecute(void);


void abCalcOpAndInit(void)
{
    abCalcOpRegister(AND_NAME, andExecute);
}


void andExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_TWO_ARGS(AND_NAME);

    if (expr1->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, AND_NAME);
        return;
    }

    if (expr2->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, AND_NAME);
        return;
    }

    abCalcExprIntSet(&result, expr2->u.integer & expr1->u.integer);

    abCalcStackExprPop(NULL);
    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
