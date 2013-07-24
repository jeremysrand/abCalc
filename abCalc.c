/* 
    abCalc.c
        By: Jeremy Rand
 */


#include "abCalcExpr.h"
#include "abCalcExprInt.h"
#include "abCalcExprReal.h"
#include "abCalcMode.h"
#include "abCalcStack.h"


void abCalcInit(void)
{
    abCalcExprInit();
    abCalcExprRealInit();
    abCalcExprIntInit();

    abCalcModeInit();
    abCalcStackInit();
}


