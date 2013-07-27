/* 
    abCOpSwap.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>
#include <string.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"

#include "ops/abCOp.h"
#include "ops/abCOpSwap.h"


#define SWAP_NAME "SWAP"


static void swapExecute(void);


void abCalcOpSwapInit(void)
{
    abCalcOpRegister(SWAP_NAME, swapExecute);
}


void swapExecute(void)
{
    abCalcExpr result1;
    abCalcExpr result2;
    AB_CALC_OP_TWO_ARGS(SWAP_NAME);

    memcpy(&result2, expr2, sizeof(result2));
    memcpy(&result1, expr1, sizeof(result1));

    abCalcStackExprPop(NULL);
    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result1);
    abCalcStackExprPush(&result2);
}
