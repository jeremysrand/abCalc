/* 
    abCalc.c
        By: Jeremy Rand
 */


#include "abCExpr.h"
#include "abCExprInt.h"
#include "abCExpReal.h"
#include "abCMode.h"
#include "abCStack.h"
#include "abCOp.h"
#include "abCError.h"


void abCalcInit(void)
{
    abCalcExprInit();
    abCalcExprRealInit();
    abCalcExprIntInit();

    abCalcModeInit();
    abCalcStackInit();

    abCalcOpInit();

    abCalcErrorInit();
}


