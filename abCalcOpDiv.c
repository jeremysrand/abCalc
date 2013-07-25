/* 
    abCalcOpDiv.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpDiv.h"

#include "abCalcOp.h"
#include "abCalcError.h"
#include "abCalcExpr.h"
#include "abCalcExpReal.h"
#include "abCalcExprInt.h"
#include "abCalcStack.h"


#define OP_NAME "/"


static void divExecute(void);


void abCalcOpDivInit(void)
{
    abCalcOpRegister(OP_NAME, divExecute);
}


void divExecute(void)
{
    abCalcExpr result;
    char expr1Real = 0;
    char expr2Real = 0;
    AB_CALC_OP_TWO_ARGS(OP_NAME);

    if (expr1->type == abCalcExprTypeReal) {
        expr1Real = 1;
        if (expr1->u.real == 0.0) {
            abCalcRaiseError(abCalcInfiniteResultError, OP_NAME);
            return;
        }
    } else if (expr1->type == abCalcExprTypeInt) {
        if (expr1->u.integer == 0l) {
            abCalcRaiseError(abCalcInfiniteResultError, OP_NAME);
            return;
        }
    } else {
        abCalcRaiseError(abCalcBadArgTypeError, OP_NAME);
        return;
    }

    if (expr2->type == abCalcExprTypeReal) {
        expr2Real = 1;
    } else if (expr2->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, OP_NAME);
        return;
    }

    if ((expr1Real) && (expr2Real)) {
        abCalcExprRealSet(&result, expr2->u.real / expr1->u.real);
    } else {
        if (expr1Real) {
            abCalcExprIntSet(&result, expr2->u.integer / (abCalcIntType)expr1->u.real);
        } else if (expr2Real) {
            abCalcExprIntSet(&result, (abCalcIntType)expr2->u.real / expr1->u.integer);
        } else {
            abCalcExprIntSet(&result, expr2->u.integer / expr1->u.integer);
        }
    }

    abCalcStackExprPop(NULL);
    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
