/* 
    abCOpDrop.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"

#include "ops/abCOp.h"
#include "ops/abCOpDrop.h"


#define DROP_NAME "DROP"


static void dropExecute(void);


void abCalcOpDropInit(void)
{
    abCalcOpRegister(DROP_NAME, dropExecute);
}


void dropExecute(void)
{
    AB_CALC_OP_ONE_ARG(DROP_NAME);

    abCalcStackExprPop(NULL);
}
