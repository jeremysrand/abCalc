/* 
    abCalcOpBin.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpBin.h"

#include "abCalcOp.h"
#include "abCalcMode.h"


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
