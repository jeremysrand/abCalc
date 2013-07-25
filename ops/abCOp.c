/* 
    abCOp.c
        By: Jeremy Rand
 */


#include <stdio.h>
#include <string.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"

#include "ops/abCOp.h"

#include "ops/abCOpAdd.h"
#include "ops/abCOpSubtr.h"
#include "ops/abCOpMult.h"
#include "ops/abCOpDiv.h"
#include "ops/abCOpPower.h"

#include "ops/abCOpAnd.h"
#include "ops/abCOpOr.h"
#include "ops/abCOpXor.h"
#include "ops/abCOpNot.h"
#include "ops/abCOpSl.h"
#include "ops/abCOpRl.h"
#include "ops/abCOpSr.h"
#include "ops/abCOpRr.h"
#include "ops/abCOpAsr.h"

#include "ops/abCOpBin.h"
#include "ops/abCOpOct.h"
#include "ops/abCOpDec.h"
#include "ops/abCOpHex.h"
#include "ops/abCOpStws.h"
#include "ops/abCOpRcws.h"


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
#ifdef ABCALC_GSOS
        if (stricmp(gOps[i].name, name) == 0) {
#else
        if (strcasecmp(gOps[i].name, name) == 0) {
#endif
            return &gOps[i];
        }
    }

    return NULL;
}


