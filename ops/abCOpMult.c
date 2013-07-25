/* 
    abCOpMult.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCOpMult.h"

#include "abCOp.h"
#include "abCError.h"
#include "abCExpr.h"
#include "abCExpReal.h"
#include "abCExprInt.h"
#include "abCStack.h"


#define OP_NAME "*"


static void multExecute(void);


void abCalcOpMultInit(void)
{
    abCalcOpRegister(OP_NAME, multExecute);
}


void multExecute(void)
{
    abCalcExpr result;
    char expr1Real = 0;
    char expr2Real = 0;
    AB_CALC_OP_TWO_ARGS(OP_NAME);

    if (expr1->type == abCalcExprTypeReal) {
        expr1Real = 1;
    } else if (expr1->type != abCalcExprTypeInt) {
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
        abCalcExprRealSet(&result, expr2->u.real * expr1->u.real);
    } else {
        if (expr1Real) {
            abCalcExprIntSet(&result, expr2->u.integer * (abCalcIntType)expr1->u.real);
        } else if (expr2Real) {
            abCalcExprIntSet(&result, (abCalcIntType)expr2->u.real * expr1->u.integer);
        } else {
            abCalcExprIntSet(&result, expr2->u.integer * expr1->u.integer);
        }
    }

    abCalcStackExprPop(NULL);
    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
