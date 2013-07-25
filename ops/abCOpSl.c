/* 
    abCOpSl.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExprInt.h"

#include "ops/abCOp.h"
#include "ops/abCOpSl.h"


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
