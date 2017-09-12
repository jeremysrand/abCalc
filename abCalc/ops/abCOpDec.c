/* 
    abCOpDec.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCMode.h"

#include "ops/abCOp.h"
#include "ops/abCOpDec.h"


#define DEC_NAME "DEC"


static void decExecute(void);


void abCalcOpDecInit(void)
{
    abCalcOpRegister(DEC_NAME, decExecute);
}


void decExecute(void)
{
    abCalcModeSetBase(abCalcModeDecBase);
}
