/* 
    abCOpPower.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"

#include "ops/abCOp.h"
#include "ops/abCOpPower.h"


#define POWER_NAME "^"


static void powerExecute(void);


void abCalcOpPowerInit(void)
{
    abCalcOpRegister(POWER_NAME, powerExecute);
}


void powerExecute(void)
{
    abCalcExpr result;
    double integral;
    AB_CALC_OP_TWO_ARGS(POWER_NAME);

    if (expr1->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, POWER_NAME);
        return;
    }

    if (expr2->type != abCalcExprTypeReal) {
        abCalcRaiseError(abCalcBadArgTypeError, POWER_NAME);
        return;
    }

	if (expr2->u.real == 0.0) {
		if (expr1->u.real < 0.0) {
            abCalcRaiseError(abCalcInfiniteResultError, POWER_NAME);
			return;
		}
		if (expr1->u.real == 0.0) {
            abCalcExprRealSet(&result, 1.0);
		} else {
            abCalcExprRealSet(&result, 0.0);
		}
	} else {
        if (expr2->u.real < 0.0) {
            modf(expr1->u.real, &integral);
            if (expr1->u.real != integral) {
                abCalcRaiseError(abCalcComplexResultError, POWER_NAME);
                return;
            }
        }

        abCalcExprRealSet(&result, pow(expr2->u.real, expr1->u.real));
    }

    abCalcStackExprPop(NULL);
    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
