/* 
    abCOpSr.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCOpSr.h"

#include "abCOp.h"
#include "abCError.h"
#include "abCExpr.h"
#include "abCExprInt.h"
#include "abCStack.h"


#define OP_NAME "SR"


static void srExecute(void);


void abCalcOpSrInit(void)
{
    abCalcOpRegister(OP_NAME, srExecute);
}


void srExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(OP_NAME);

    if (expr->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, OP_NAME);
        return;
    }

    abCalcExprIntSet(&result, (expr->u.integer >> 1));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
