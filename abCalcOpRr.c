/* 
    abCalcOpRr.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpRr.h"

#include "abCalcOp.h"
#include "abCalcError.h"
#include "abCalcExpr.h"
#include "abCalcMode.h"
#include "abCalcStack.h"
#include "abCalcExprInt.h"


#define OP_NAME "RR"


static void rrExecute(void);


void abCalcOpRrInit(void)
{
    abCalcOpRegister(OP_NAME, rrExecute);
}


void rrExecute(void)
{
    abCalcExpr result;
    int width;
    abCalcIntType bottomBit;
    AB_CALC_OP_ONE_ARG(OP_NAME);

    if (expr->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, OP_NAME);
        return;
    }

	width = abCalcModeGetIntWidth();
	bottomBit = (expr->u.integer & 1);

    abCalcExprIntSet(&result, ((expr->u.integer >> 1) | (bottomBit << (width - 1))));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
