/* 
    abCStack.c
        By: Jeremy Rand
 */


#include <stdlib.h>
#include <string.h>

#include "abCStack.h"
#include "abCError.h"


#define AB_CALC_STACK_DEPTH 128


static abCalcExpr gStack[AB_CALC_STACK_DEPTH];
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
