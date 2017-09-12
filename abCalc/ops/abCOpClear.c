/* 
    abCOpClear.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>

#include "abCStack.h"

#include "ops/abCOp.h"
#include "ops/abCOpClear.h"


#define CLEAR_NAME "CLEAR"


static void clearExecute(void);


void abCalcOpClearInit(void)
{
    abCalcOpRegister(CLEAR_NAME, clearExecute);
}


void clearExecute(void)
{
    abCalcStackClear();
}
