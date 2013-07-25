/* 
    abCOpHex.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCMode.h"

#include "ops/abCOp.h"
#include "ops/abCOpHex.h"


#define OP_NAME "HEX"


static void hexExecute(void);


void abCalcOpHexInit(void)
{
    abCalcOpRegister(OP_NAME, hexExecute);
}


void hexExecute(void)
{
    abCalcModeSetBase(abCalcModeHexBase);
}
