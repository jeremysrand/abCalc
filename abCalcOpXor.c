/* 
    abCalcOpXor.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpXor.h"

#include "abCalcOp.h"
#include "abCalcError.h"
#include "abCalcExpr.h"
#include "abCalcStack.h"


#define OP_NAME "XOR"


static void xorExecute(void);


void abCalcOpXorInit(void)
{
    abCalcOpRegister(OP_NAME, xorExecute);
}


void xorExecute(void)
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

    result.type = abCalcExprTypeInt;
    result.u.integer = expr2->u.integer ^ expr1->u.integer;

    abCalcStackExprPop(NULL);
    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
