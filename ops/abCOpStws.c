/* 
    abCOpStws.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"
#include "abCMode.h"

#include "expr/abCExpr.h"

#include "ops/abCOp.h"
#include "ops/abCOpStws.h"


#define OP_NAME "STWS"


static void stwsExecute(void);


void abCalcOpStwsInit(void)
{
    abCalcOpRegister(OP_NAME, stwsExecute);
}


void stwsExecute(void)
{
    int newWidth;
    AB_CALC_OP_ONE_ARG(OP_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, OP_NAME);
        return;
    }

    newWidth = (int)expr->u.real;
    if ((newWidth < 1) ||
        (newWidth > AB_CALC_EXPR_MAX_INT_WIDTH)) {
        abCalcRaiseError(abCalcBadArgValueError, OP_NAME);
        return;
    }

    abCalcModeSetIntWidth(newWidth);
    abCalcStackExprPop(NULL);
}
