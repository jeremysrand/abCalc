/* 
    abCalcOpHex.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpHex.h"

#include "abCalcOp.h"
#include "abCalcMode.h"


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
