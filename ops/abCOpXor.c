/* 
    abCOpXor.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCOpXor.h"

#include "abCOp.h"
#include "abCError.h"
#include "abCExpr.h"
#include "abCExprInt.h"
#include "abCStack.h"


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

    abCalcExprIntSet(&result, expr2->u.integer ^ expr1->u.integer);

    abCalcStackExprPop(NULL);
    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
