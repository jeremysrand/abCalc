/* 
    abCalcOp.c
        By: Jeremy Rand
 */


#include <stdio.h>
#include <string.h>

#include "abCalcOp.h"

#include "abCalcOpAdd.h"


#define AB_CALC_MAX_OPS 128


static abCalcOp gOps[AB_CALC_MAX_OPS];
static int gNumOps = 0;


void abCalcOpInit(void)
{
    memset(gOps, 0, sizeof(gOps));

    abCalcOpAddInit();
}


void abCalcOpRegister(char *name, void (*execute)(void))
{
    if (gNumOps >= AB_CALC_MAX_OPS) {
        fprintf(stderr, "Operation registration overflow");
        return;
    }

    gOps[gNumOps].name = name;
    gOps[gNumOps].execute = execute;
    gNumOps++;
}


abCalcOp *abCalcOpLookup(char *name)
{
    int i;

    for (i = 0; i < gNumOps; i++) {
        if (strcmp(gOps[i].name, name) == 0) {
            return &gOps[i];
        }
    }

    return NULL;
}
