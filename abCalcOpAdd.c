/* 
    abCalcOpAdd.c
        By: Jeremy Rand
 */


#include <stdio.h>

#include "abCalcOpAdd.h"
#include "abCalcOp.h"


#define OP_NAME "+"


static void addExecute(void);


void abCalcOpAddInit(void)
{
    abCalcOpRegister(OP_NAME, addExecute);
}


void addExecute(void)
{
    printf("In add!\n");
}
