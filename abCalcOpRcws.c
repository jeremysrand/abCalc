/* 
    abCalcOpRcws.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpRcws.h"

#include "abCalcOp.h"
#include "abCalcExpr.h"
#include "abCalcExpReal.h"
#include "abCalcStack.h"
#include "abCalcMode.h"


#define OP_NAME "RCWS"


static void rcwsExecute(void);


void abCalcOpRcwsInit(void)
{
    abCalcOpRegister(OP_NAME, rcwsExecute);
}


void rcwsExecute(void)
{
    abCalcExpr result;

    abCalcExprRealSet(&result, (abCalcRealType)abCalcModeGetIntWidth());

    abCalcStackExprPush(&result);
}
