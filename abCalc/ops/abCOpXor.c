/* 
    abCOpXor.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExprInt.h"

#include "ops/abCOp.h"
#include "ops/abCOpXor.h"


#define XOR_NAME "XOR"


static void xorExecute(void);


void abCalcOpXorInit(void)
{
    abCalcOpRegister(XOR_NAME, xorExecute);
}


void xorExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_TWO_ARGS(XOR_NAME);

    if (expr1->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, XOR_NAME);
        return;
    }

    if (expr2->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, XOR_NAME);
        return;
    }

    abCalcExprIntSet(&result, expr2->u.integer ^ expr1->u.integer);

    abCalcStackExprPop(NULL);
    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
