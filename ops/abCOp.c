/* 
    abCOp.c
        By: Jeremy Rand
 */


#include <stdio.h>
#include <string.h>

#include "abCOp.h"
#include "abCExpr.h"
#include "abCError.h"
#include "abCStack.h"

#include "abCOpAdd.h"
#include "abCOpSubtr.h"
#include "abCOpMult.h"
#include "abCOpDiv.h"
#include "abCOpPower.h"

#include "abCOpAnd.h"
#include "abCOpOr.h"
#include "abCOpXor.h"
#include "abCOpNot.h"
#include "abCOpSl.h"
#include "abCOpRl.h"
#include "abCOpSr.h"
#include "abCOpRr.h"
#include "abCOpAsr.h"

#include "abCOpBin.h"
#include "abCOpOct.h"
#include "abCOpDec.h"
#include "abCOpHex.h"
#include "abCOpStws.h"
#include "abCOpRcws.h"


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
    abCalcOpSlInit();
    abCalcOpRlInit();
    abCalcOpSrInit();
    abCalcOpRrInit();
    abCalcOpAsrInit();

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


