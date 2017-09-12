/* 
    abCStack.c
        By: Jeremy Rand
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abCStack.h"
#include "abCError.h"


abCalcExpr gStack[AB_CALC_STACK_DEPTH];
static int gStackNumItems = 0;


void abCalcStackInit(void)
{
}


abCalcExpr *abCalcStackExprPush(abCalcExpr *expr)
{
    abCalcExpr *result = NULL;

    if (gStackNumItems >= AB_CALC_STACK_DEPTH) {
        abCalcRaiseError(abCalcStackFullError, NULL);
        return NULL;
    }

    if ((gStackNumItems < AB_CALC_STACK_DEPTH) &&
        (expr != NULL)) {
        result = &(gStack[gStackNumItems]);
        memcpy(result, expr, sizeof(*expr));
        gStackNumItems++;
    }
    return result;
}


abCalcExpr *abCalcStackExprPop(abCalcExpr *expr)
{
    abCalcExpr *result = NULL;

    if (gStackNumItems < 1)
        return NULL;

    gStackNumItems--;

    if (expr != NULL) {
        result = expr;
        memcpy(expr, &(gStack[gStackNumItems]), sizeof(*expr));
    }

    return result;
}


int abCalcStackNumItems(void)
{
    return gStackNumItems;
}


abCalcExpr *abCalcStackExprAt(int depth)
{
    abCalcExpr *result = NULL;
    if (depth < gStackNumItems) {
        result = &(gStack[gStackNumItems - 1 - depth]);
    }

    return result;
}


char *abCalcStackExprStringAt(int depth, char *buffer, int addPrefix)
{
    static char tmpBuffer[AB_CALC_EXPR_STRING_MAX];

    if (buffer == NULL)
        return NULL;

    if (addPrefix) {
        sprintf(buffer, "%3d: ", depth + 1);
    } else {
        buffer[0] = '\0';
    }
    if (depth < gStackNumItems) {
        if (abCalcFormatExpr(&(gStack[gStackNumItems - 1 - depth]), tmpBuffer) != NULL) {
            strcat(buffer, tmpBuffer);
        }
    }

    return buffer;
}


void abCalcStackClear(void)
{
    gStackNumItems = 0;
}
