/* 
    abCOpRcws.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCOpRcws.h"

#include "abCOp.h"
#include "abCExpr.h"
#include "abCExpReal.h"
#include "abCStack.h"
#include "abCMode.h"


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
