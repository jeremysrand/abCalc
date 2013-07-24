/* 
    abCalcError.c
        By: Jeremy Rand
 */


#include <stdio.h>
#include <stdlib.h>

#include "abCalcError.h"


static char *gErrorStrings[abCalcErrorTypeMax];

static abCalcErrorType gCurrErrorType = abCalcNoError;
static char *gCurrErrorOpName = NULL;

static char gErrorBuffer[128];


void abCalcErrorInit(void)
{
    gErrorStrings[abCalcNoError] = NULL;
    gErrorStrings[abCalcSyntaxError] = "Syntax Error";
    gErrorStrings[abCalcBadArgTypeError] = "Bad Argument Type";
    gErrorStrings[abCalcBadArgValueError] = "Bad Argument Value";
    gErrorStrings[abCalcTooFewArgsError] = "Too Few Arguments";
    gErrorStrings[abCalcStackFullError] = "Stack Full";
    gErrorStrings[abCalcInfiniteResultError] = "Infinite Result";
    gErrorStrings[abCalcComplexResultError] = "Complex Result";
}


void abCalcRaiseError(abCalcErrorType type, char *opName)
{
    if ((type < abCalcErrorTypeMin) ||
        (type >= abCalcErrorTypeMax))
        return;

    if (gCurrErrorType == abCalcNoError) {
        gCurrErrorType = type;
        gCurrErrorOpName = opName;
    }
}


char *abCalcGetError(void)
{
    char *errorString;

    if ((gCurrErrorType < abCalcErrorTypeMin) ||
        (gCurrErrorType >= abCalcErrorTypeMax))
        return NULL;

    errorString = gErrorStrings[gCurrErrorType];

    if (errorString == NULL)
        return NULL;

    if (gCurrErrorOpName != NULL) {
        sprintf(gErrorBuffer, "%s Error: %s", gCurrErrorOpName, gErrorStrings[gCurrErrorType]);
    } else {
        sprintf(gErrorBuffer, "Error: %s", gErrorStrings[gCurrErrorType]);
    }

    return gErrorBuffer;
}


void abCalcClearError(void)
{
    gCurrErrorType = abCalcNoError;
    gCurrErrorOpName = NULL;
}

