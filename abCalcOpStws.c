/* 
    abCalcOpStws.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpStws.h"

#include "abCalcOp.h"
#include "abCalcExpr.h"
#include "abCalcError.h"
#include "abCalcStack.h"
#include "abCalcMode.h"


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
