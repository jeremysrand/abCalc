/* 
    abCalc.c
        By: Jeremy Rand
 */


#include "abCMode.h"
#include "abCStack.h"
#include "abCError.h"

#include "expr/abCExpr.h"
#include "expr/abCExprInt.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"


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


