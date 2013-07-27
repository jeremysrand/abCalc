/* 
    abCOpAtan.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpAtan.h"


#define ATAN_NAME "ATAN"


static void atanExecute(void);


void abCalcOpAtanInit(void)
{
    abCalcOpRegister(ATAN_NAME, atanExecute);
}


void atanExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(ATAN_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, ATAN_NAME);
        return;
    }

    abCalcExprRealSet(&result, atan(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
