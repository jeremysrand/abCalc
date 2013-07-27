/* 
    abCOp.c
        By: Jeremy Rand
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "abCError.h"
#include "abCStack.h"

#include "expr/abCExpr.h"

#include "ops/abCOp.h"

#include "ops/abCOpAdd.h"
#include "ops/abCOpSubtr.h"
#include "ops/abCOpMult.h"
#include "ops/abCOpDiv.h"
#include "ops/abCOpChs.h"
#include "ops/abCOpInv.h"
#include "ops/abCOpSq.h"
#include "ops/abCOpSqrt.h"
#include "ops/abCOpPower.h"

#include "ops/abCOpDrop.h"
#include "ops/abCOpSwap.h"
#include "ops/abCOpClear.h"

#include "ops/abCOpPi.h"
#include "ops/abCOpSin.h"
#include "ops/abCOpCos.h"
#include "ops/abCOpTan.h"
#include "ops/abCOpAsin.h"
#include "ops/abCOpAcos.h"
#include "ops/abCOpAtan.h"

#include "ops/abCOpLog.h"
#include "ops/abCOpAlog.h"
#include "ops/abCOpLn.h"
#include "ops/abCOpExp.h"
#include "ops/abCOpSinh.h"
#include "ops/abCOpCosh.h"
#include "ops/abCOpTanh.h"

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


abCalcOp gOps[AB_CALC_MAX_OPS];
static int gNumOps = 0;


void abCalcOpInit(void)
{
    memset(gOps, 0, sizeof(gOps));

    abCalcOpAddInit();
    abCalcOpSubtrInit();
    abCalcOpMultInit();
    abCalcOpDivInit();
    abCalcOpChsInit();
    abCalcOpInvInit();
    abCalcOpSqInit();
    abCalcOpSqrtInit();
    abCalcOpPowerInit();

    abCalcOpDropInit();
    abCalcOpSwapInit();
    abCalcOpClearInit();

    abCalcOpPiInit();
    abCalcOpSinInit();
    abCalcOpCosInit();
    abCalcOpTanInit();
    abCalcOpAsinInit();
    abCalcOpAcosInit();
    abCalcOpAtanInit();

    abCalcOpLogInit();
    abCalcOpAlogInit();
    abCalcOpLnInit();
    abCalcOpExpInit();
    abCalcOpSinhInit();
    abCalcOpCoshInit();
    abCalcOpTanhInit();

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


abCalcOp *abCalcOpNth(int n)
{
    if ((n < 0) ||
        (n >= gNumOps))
        return NULL;

    return &gOps[n];
}


int abCalcOpNumOps(void)
{
    return gNumOps;
}
