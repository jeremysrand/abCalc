/* 
    abCOpTan.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpTan.h"


#define TAN_NAME "TAN"


static void tanExecute(void);


void abCalcOpTanInit(void)
{
    abCalcOpRegister(TAN_NAME, tanExecute);
}


void tanExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(TAN_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, TAN_NAME);
        return;
    }

    abCalcExprRealSet(&result, tan(expr->u.real));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
