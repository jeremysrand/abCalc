/* 
    abCOpOct.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCOpOct.h"

#include "abCOp.h"
#include "abCMode.h"


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
