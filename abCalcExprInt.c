/* 
    abCalcExprInt.c
        By: Jeremy Rand
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "abCalcExpr.h"
#include "abCalcMode.h"


static abCalcExpr *abCalcExprIntParse(abCalcExpr *expr, char *buffer);
static char *abCalcExprIntFormat(abCalcExpr *expr, char *buffer);


static abCalcExprCallbacks gCallbacks = {
    abCalcExprIntParse,
    abCalcExprIntFormat
};


void abCalcExprIntInit(void)
{
    abCalcRegisterExprType(abCalcExprTypeInt, &gCallbacks);
}


abCalcExpr *abCalcExprIntParse(abCalcExpr *expr, char *buffer)
{
    abCalcModeIntBase base = abCalcModeGetBase();
    abCalcIntType value = 0;
    int len;
    int offset;

    if (buffer == NULL)
        return NULL;

    if (expr == NULL)
        return NULL;

    len = strlen(buffer);
    if (len < 2)
        return NULL;

    if (buffer[0] != '#')
        return NULL;

    switch (base) {
        case abCalcModeBinBase:
            for (offset = 1; offset < len; offset++) {
                value <<= 1;
                switch (buffer[offset]) {
                    case '1':
                        value++;
                        break;

                    case '0':
                        break;
                        
                    default:
                        return NULL;
                }
            }
            break;

        case abCalcModeOctBase:
            for (offset = 1; offset < len; offset++) {
                value <<= 3;
                switch (buffer[offset]) {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                        value += (buffer[offset] - '0');;
                        break;
                        
                    default:
                        return NULL;
                }
            }
            break;

        case abCalcModeDecBase:
            for (offset = 1; offset < len; offset++) {
                value *= 10;
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
                        value += (buffer[offset] - '0');;
                        break;
                        
                    default:
                        return NULL;
                }
            }
            break;

        case abCalcModeHexBase:
            for (offset = 1; offset < len; offset++) {
                value <<= 4;
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
                        value += (buffer[offset] - '0');;
                        break;

                    case 'a':
                    case 'A':
                        value += 10;
                        break;

                    case 'b':
                    case 'B':
                        value += 11;
                        break;
                        
                    case 'c':
                    case 'C':
                        value += 12;
                        break;
                        
                    case 'd':
                    case 'D':
                        value += 13;
                        break;
                        
                    case 'e':
                    case 'E':
                        value += 14;
                        break;
                        
                    case 'f':
                    case 'F':
                        value += 15;
                        break;
                        
                    default:
                        return NULL;
                }
            }
            break;

        default:
            return NULL;
    }

    expr->type = abCalcExprTypeInt;
    expr->u.integer = value;
    return expr;
}


char *abCalcExprIntFormat(abCalcExpr *expr, char *buffer)
{
    abCalcModeIntBase base = abCalcModeGetBase();
    int width = abCalcModeGetIntWidth();
    abCalcIntType value;
    char *ptr;
    int gotFirstOne;
    int i;

    if (expr == NULL)
        return NULL;

    if (buffer == NULL)
        return NULL;

    if (expr->type != abCalcExprTypeInt)
        return NULL;

    value = expr->u.integer;

    if (width < AB_CALC_EXPR_MAX_INT_WIDTH) {
        value &= ((1l << width) - 1);
    }

    switch (base) {
        case abCalcModeBinBase:
		    gotFirstOne = 0;
            ptr = buffer;
            *ptr = '#';
            ptr++;
		
		    for (i = width - 1; i >= 0; i--) {
                if ((value >> i) & 1) {
                    *ptr = '1';
                    ptr++;
                    gotFirstOne = 1;
                } else {
                    if (gotFirstOne) {
                        *ptr = '0';
                        ptr++;
                    }
                }
            }
		    if (!gotFirstOne) {
                *ptr = '0';
                ptr++;
            }
            *ptr = ' ';
            ptr++;
            *ptr = 'b';
            ptr++;
            *ptr = '\0';
            break;
            
        case abCalcModeOctBase:
            sprintf(buffer, "#%lo o", value);
            break;

        case abCalcModeDecBase:
            sprintf(buffer, "#%lu d", value);
            break;

        case abCalcModeHexBase:
            sprintf(buffer, "#%lX h", value);
            break;

        default:
            return NULL;
    }

    return buffer;
}


void abCalcExprIntSet(abCalcExpr *expr, abCalcIntType value)
{
    int width;

    if (expr == NULL)
        return;

    width = abCalcModeGetIntWidth();

    expr->type = abCalcExprTypeInt;
    expr->u.integer = value;

    if (width < AB_CALC_EXPR_MAX_INT_WIDTH) {
        expr->u.integer &= ((1l << width) - 1);
    }
}
