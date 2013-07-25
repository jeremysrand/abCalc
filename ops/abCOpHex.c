/* 
    abCOpHex.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCOpHex.h"

#include "abCOp.h"
#include "abCMode.h"


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
