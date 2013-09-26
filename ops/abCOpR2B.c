/* 
    abCOpR2B.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"
#include "expr/abCExprInt.h"

#include "ops/abCOp.h"
#include "ops/abCOpR2B.h"


#define R2B_NAME "R2B"


static void r2bExecute(void);


void abCalcOpR2BInit(void)
{
    abCalcOpRegister(R2B_NAME, r2bExecute);
}


void r2bExecute(void)
{
    abCalcExpr result;
    int width;
    int topBit;
    AB_CALC_OP_ONE_ARG(R2B_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, R2B_NAME);
        return;
    }

    abCalcExprIntSet(&result, (abCalcIntType)expr->u.real);

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
