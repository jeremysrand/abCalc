/* 
    abCOpBin.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCOpBin.h"

#include "abCOp.h"
#include "abCMode.h"


#define OP_NAME "BIN"


static void binExecute(void);


void abCalcOpBinInit(void)
{
    abCalcOpRegister(OP_NAME, binExecute);
}


void binExecute(void)
{
    abCalcModeSetBase(abCalcModeBinBase);
}
