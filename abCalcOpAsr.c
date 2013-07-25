/* 
    abCalcOpAsr.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpAsr.h"

#include "abCalcOp.h"
#include "abCalcError.h"
#include "abCalcExpr.h"
#include "abCalcExprInt.h"
#include "abCalcMode.h"
#include "abCalcStack.h"


#define OP_NAME "ASR"


static void asrExecute(void);


void abCalcOpAsrInit(void)
{
    abCalcOpRegister(OP_NAME, asrExecute);
}


void asrExecute(void)
{
    abCalcExpr result;
    int width;
    abCalcIntType upperBit;
    AB_CALC_OP_ONE_ARG(OP_NAME);

    if (expr->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, OP_NAME);
        return;
    }

	width = abCalcModeGetIntWidth();
	upperBit = (expr->u.integer & (1 << (width - 1)));
	
    abCalcExprIntSet(&result, ((expr->u.integer >> 1) | upperBit));

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
