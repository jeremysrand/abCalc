/* 
    abCOpOct.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCMode.h"

#include "ops/abCOp.h"
#include "ops/abCOpOct.h"


#define OCT_NAME "OCT"


static void octExecute(void);


void abCalcOpOctInit(void)
{
    abCalcOpRegister(OCT_NAME, octExecute);
}


void octExecute(void)
{
    abCalcModeSetBase(abCalcModeOctBase);
}
