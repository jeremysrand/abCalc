/* 
    abCOpOct.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCMode.h"

#include "ops/abCOp.h"
#include "ops/abCOpOct.h"


#define OP_NAME "OCT"


static void octExecute(void);


void abCalcOpOctInit(void)
{
    abCalcOpRegister(OP_NAME, octExecute);
}


void octExecute(void)
{
    abCalcModeSetBase(abCalcModeOctBase);
}
