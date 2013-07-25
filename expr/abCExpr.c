/* 
    abCExpr.c
        By: Jeremy Rand
 */


#include <stdlib.h>

#include "expr/abCExpr.h"


static abCalcExprCallbacks *gCallbacks[abCalcExprTypeMax];


#define AB_CALC_EXPR_TYPE_INVALID(type) (((type) < abCalcExprTypeMin) || ((type) >= abCalcExprTypeMax))

void abCalcExprInit(void)
{
    abCalcExprType type;

    for (type = abCalcExprTypeMin; type < abCalcExprTypeMax; type++) {
        gCallbacks[type] = NULL;
    }
}


void abCalcRegisterExprType(abCalcExprType type, abCalcExprCallbacks *callbacks)
{
    if (AB_CALC_EXPR_TYPE_INVALID(type))
        return;

    gCallbacks[type] = callbacks;
}


abCalcExpr *abCalcParseExpr(abCalcExpr *expr, char *buffer)
{
    abCalcExpr *result = NULL;
    abCalcExprType type;

    for (type = abCalcExprTypeMin; type < abCalcExprTypeMax; type++) {
        if (gCallbacks[type] != NULL) {
            result = (gCallbacks[type]->parseExpr)(expr, buffer);
            if (result != NULL)
                return result;
        }
    }
    return result;
}


char *abCalcFormatExpr(abCalcExpr *expr, char *buffer)
{
    if (AB_CALC_EXPR_TYPE_INVALID(expr->type))
        return NULL;

    if (gCallbacks[expr->type] == NULL)
        return NULL;

    return (gCallbacks[expr->type]->formatExpr(expr, buffer));
}
