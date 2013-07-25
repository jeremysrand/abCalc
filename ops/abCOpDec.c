/* 
    abCOpDec.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCMode.h"

#include "ops/abCOp.h"
#include "ops/abCOpDec.h"


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
