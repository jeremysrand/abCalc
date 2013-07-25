/* 
    abCOpRr.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCError.h"
#include "abCMode.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExprInt.h"

#include "ops/abCOp.h"
#include "ops/abCOpRr.h"


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
