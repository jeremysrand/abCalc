/* 
    abCOpDec.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCOpDec.h"

#include "abCOp.h"
#include "abCMode.h"


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
