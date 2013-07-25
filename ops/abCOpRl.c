/* 
    abCOpRl.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCError.h"
#include "abCMode.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExprInt.h"

#include "ops/abCOp.h"
#include "ops/abCOpRl.h"


#define OP_NAME "RL"


static void rlExecute(void);


void abCalcOpRlInit(void)
{
    abCalcOpRegister(OP_NAME, rlExecute);
}


void rlExecute(void)
{
    abCalcExpr result;
    int width;
    int topBit;
    AB_CALC_OP_ONE_ARG(OP_NAME);

    if (expr->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, OP_NAME);
        return;
    }

	width = abCalcModeGetIntWidth();
	topBit = ((expr->u.integer >> (width - 1)) & 1);

    abCalcExprIntSet(&result, ((expr->u.integer << 1) | topBit));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
