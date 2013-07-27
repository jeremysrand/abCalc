/* 
    abCOpPi.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpPi.h"


#define PI_NAME "PI"


static void piExecute(void);


void abCalcOpPiInit(void)
{
    abCalcOpRegister(PI_NAME, piExecute);
}


void piExecute(void)
{
    abCalcExpr result;

#ifdef ABCALC_GSOS
    abCalcExprRealSet(&result, 2.0 * asin(1.0));
#else
    abCalcExprRealSet(&result, M_PI);
#endif

    abCalcStackExprPush(&result);
}
