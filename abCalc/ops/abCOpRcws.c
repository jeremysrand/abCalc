/* 
    abCOpRcws.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCStack.h"
#include "abCMode.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpRcws.h"


#define RCWS_NAME "RCWS"


static void rcwsExecute(void);


void abCalcOpRcwsInit(void)
{
    abCalcOpRegister(RCWS_NAME, rcwsExecute);
}


void rcwsExecute(void)
{
    abCalcExpr result;

    abCalcExprRealSet(&result, (abCalcRealType)abCalcModeGetIntWidth());

    abCalcStackExprPush(&result);
}
