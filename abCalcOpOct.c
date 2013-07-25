/* 
    abCalcOpOct.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpOct.h"

#include "abCalcOp.h"
#include "abCalcMode.h"


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
