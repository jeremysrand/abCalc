/* 
    abCOpAsr.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCError.h"
#include "abCMode.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExprInt.h"

#include "ops/abCOp.h"
#include "ops/abCOpAsr.h"


#define ASR_NAME "ASR"


static void asrExecute(void);


void abCalcOpAsrInit(void)
{
    abCalcOpRegister(ASR_NAME, asrExecute);
}


void asrExecute(void)
{
    abCalcExpr result;
    int width;
    abCalcIntType upperBit;
    AB_CALC_OP_ONE_ARG(ASR_NAME);

    if (expr->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, ASR_NAME);
        return;
    }

	width = abCalcModeGetIntWidth();
	upperBit = (expr->u.integer & (1 << (width - 1)));
	
    abCalcExprIntSet(&result, ((expr->u.integer >> 1) | upperBit));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
