/* 
    abCalcOpDec.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpDec.h"

#include "abCalcOp.h"
#include "abCalcMode.h"


#define OP_NAME "DEC"


static void decExecute(void);


void abCalcOpDecInit(void)
{
    abCalcOpRegister(OP_NAME, decExecute);
}


void decExecute(void)
{
    abCalcModeSetBase(abCalcModeDecBase);
}
