/* 
    abCOpBin.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCMode.h"

#include "ops/abCOp.h"
#include "ops/abCOpBin.h"


#define BIN_NAME "BIN"


static void binExecute(void);


void abCalcOpBinInit(void)
{
    abCalcOpRegister(BIN_NAME, binExecute);
}


void binExecute(void)
{
    abCalcModeSetBase(abCalcModeBinBase);
}
