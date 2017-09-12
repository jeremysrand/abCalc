/* 
    abCOpChs.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpChs.h"


#define CHS_NAME "CHS"


static void chsExecute(void);


void abCalcOpChsInit(void)
{
    abCalcOpRegister(CHS_NAME, chsExecute);
}


void chsExecute(void)
{
    abCalcExpr result;
    AB_CALC_OP_ONE_ARG(CHS_NAME);

    if (expr->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, CHS_NAME);
        return;
    }

    abCalcExprRealSet(&result, -1.0 * expr->u.real);

    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
