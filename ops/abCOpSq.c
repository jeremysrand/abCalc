/* 
    abCOpSq.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpSq.h"


#define SQ_NAME "SQ"


static void sqExecute(void);


void abCalcOpSqInit(void)
{
    abCalcOpRegister(SQ_NAME, sqExecute);
}


void sqExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(SQ_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, SQ_NAME);
        return;
    }

    abCalcExprRealSet(&result, expr->u.real * expr->u.real);

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
