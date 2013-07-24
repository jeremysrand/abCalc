/* 
    abCalcExprReal.c
        By: Jeremy Rand
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "abCalcExpr.h"


static abCalcExpr *abCalcExprRealParse(abCalcExpr *expr, char *buffer);
static char *abCalcExprRealFormat(abCalcExpr *expr, char *buffer);


static abCalcExprCallbacks gCallbacks = {
    abCalcExprRealParse,
    abCalcExprRealFormat
};


abCalcExpr *abCalcExprRealParse(abCalcExpr *expr, char *buffer)
{
    int offset;
    int expOffset = -1;
    int periodOffset = -1;
    int len;

    /* First validate */
    if (buffer == NULL)
        return NULL;

    len = strlen(buffer);

    for (offset = 0; offset < len; offset++) {
        switch (buffer[offset]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                break;

            case '.':
                if (periodOffset != -1)
                    return NULL;
                periodOffset = offset;
                break;

            case '-':
                if (offset == 0)
                    break;
                /* Fallthrough */
            case '+':
                if ((expOffset == -1) ||
                    ((expOffset + 1) != offset))
                    return NULL;
                break;

            case 'e':
            case 'E':
                if (expOffset != -1)
                    return NULL;
                expOffset = offset;
                break;

            default:
                return NULL;
        }
    }
    
    expr->type = abCalcExprTypeReal;
    expr->u.real = atof(buffer);
    return expr;
}


char *abCalcExprRealFormat(abCalcExpr *expr, char *buffer)
{
    if (expr == NULL)
        return NULL;

    if (buffer == NULL)
        return NULL;

    if (expr->type != abCalcExprTypeReal)
        return NULL;

    sprintf(buffer, "%f", expr->u.real);
    return buffer;
}
