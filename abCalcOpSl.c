/* 
    abCalcOpSl.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpSl.h"

#include "abCalcOp.h"
#include "abCalcError.h"
#include "abCalcExpr.h"
#include "abCalcExprInt.h"
#include "abCalcStack.h"


#define OP_NAME "SL"


static void slExecute(void);


void abCalcOpSlInit(void)
{
    abCalcOpRegister(OP_NAME, slExecute);
}


void slExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(OP_NAME);

    if (expr->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, OP_NAME);
        return;
    }

    abCalcExprIntSet(&result, (expr->u.integer << 1));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
