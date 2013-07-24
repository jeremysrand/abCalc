/* 
    abCalcMain.c
        By: Jeremy Rand
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "abCalc.h"
#include "abCalcExpr.h"
#include "abCalcStack.h"
#include "abCalcOp.h"
#include "abCalcError.h"


char gBuffer[AB_CALC_EXPR_STRING_MAX];
abCalcExpr gExpr;


int main(void)
{
    int timeToQuit = 0;
    int depth;
    int item;
    int len;
    abCalcOp *op;
    char *errorString;

    abCalcInit();

    while (!timeToQuit) {
        printf("Stack:\n");
        depth = abCalcStackNumItems();

        if (depth == 0) {
            printf("    Empty!\n");
        } else {
            for(item = depth - 1; item >= 0; item--) {
                abCalcFormatExpr(abCalcStackExprAt(item), gBuffer);
                printf("    %3d: %s\n", item + 1, gBuffer);
            }
        }

        errorString = abCalcGetError();
        if (errorString != NULL) {
            printf("\n   %s\n", errorString);
            abCalcClearError();
        }

        timeToQuit = 1;
        if (fgets(gBuffer, sizeof(gBuffer), stdin) != NULL) {
            len = strlen(gBuffer);
            if ((gBuffer[len - 1] == '\r') ||
                (gBuffer[len - 1] == '\n')) {
                gBuffer[len - 1] = '\0';
            }

            op = abCalcOpLookup(gBuffer);

            if (op != NULL) {
                op->execute();
            } else if (abCalcParseExpr(&gExpr, gBuffer) != NULL) {
                abCalcStackExprPush(&gExpr);
            } else {
                abCalcRaiseError(abCalcSyntaxError, NULL);
            }
        }
    }

    exit(0);
}
