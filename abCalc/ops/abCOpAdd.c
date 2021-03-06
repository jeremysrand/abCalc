/* 
    abCOpAdd.c
        By: Jeremy Rand
 */


#include <stdio.h>


#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"
#include "expr/abCExpReal.h"
#include "expr/abCExprInt.h"

#include "ops/abCOp.h"
#include "ops/abCOpAdd.h"


#define ADD_NAME "+"


static void addExecute(void);


void abCalcOpAddInit(void)
{
    abCalcOpRegister(ADD_NAME, addExecute);
}


void addExecute(void)
{
    abCalcExpr result;
    char expr1Real = 0;
    char expr2Real = 0;
    AB_CALC_OP_TWO_ARGS(ADD_NAME);

    if (expr1->type == abCalcExprTypeReal) {
        expr1Real = 1;
    } else if (expr1->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, ADD_NAME);
        return;
    }

    if (expr2->type == abCalcExprTypeReal) {
        expr2Real = 1;
    } else if (expr2->type != abCalcExprTypeInt) {
        abCalcRaiseError(abCalcBadArgTypeError, ADD_NAME);
        return;
    }

    if ((expr1Real) && (expr2Real)) {
        abCalcExprRealSet(&result, expr2->u.real + expr1->u.real);
    } else {
        if (expr1Real) {
            abCalcExprIntSet(&result, expr2->u.integer + (abCalcIntType)expr1->u.real);
        } else if (expr2Real) {
            abCalcExprIntSet(&result, (abCalcIntType)expr2->u.real + expr1->u.integer);
        } else {
            abCalcExprIntSet(&result, expr2->u.integer + expr1->u.integer);
        }
    }

    abCalcStackExprPop(NULL);
    abCalcStackExprPop(NULL);
    abCalcStackExprPush(&result);
}
