/* 
    abCalcOp.c
        By: Jeremy Rand
 */


#include <stdio.h>
#include <string.h>

#include "abCalcOp.h"
#include "abCalcExpr.h"
#include "abCalcError.h"
#include "abCalcStack.h"

#include "abCalcOpAdd.h"
#include "abCalcOpSubtr.h"
#include "abCalcOpMult.h"
#include "abCalcOpDiv.h"
#include "abCalcOpPower.h"

#include "abCalcOpAnd.h"
#include "abCalcOpOr.h"
#include "abCalcOpXor.h"
#include "abCalcOpNot.h"

#include "abCalcOpBin.h"
#include "abCalcOpOct.h"
#include "abCalcOpDec.h"
#include "abCalcOpHex.h"
#include "abCalcOpStws.h"
#include "abCalcOpRcws.h"


#define AB_CALC_MAX_OPS 128


static abCalcOp gOps[AB_CALC_MAX_OPS];
static int gNumOps = 0;


void abCalcOpInit(void)
{
    memset(gOps, 0, sizeof(gOps));

    abCalcOpAddInit();
    abCalcOpSubtrInit();
    abCalcOpMultInit();
    abCalcOpDivInit();
    abCalcOpPowerInit();

    abCalcOpAndInit();
    abCalcOpOrInit();
    abCalcOpXorInit();
    abCalcOpNotInit();

    abCalcOpBinInit();
    abCalcOpOctInit();
    abCalcOpDecInit();
    abCalcOpHexInit();
    abCalcOpStwsInit();
    abCalcOpRcwsInit();
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


