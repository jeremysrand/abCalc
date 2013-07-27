/* 
    abCExpReal.c
        By: Jeremy Rand
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "expr/abCExpr.h"


static abCalcExpr *abCalcExprRealParse(abCalcExpr *expr, char *buffer);
static char *abCalcExprRealFormat(abCalcExpr *expr, char *buffer);


static abCalcExprCallbacks gRealCallbacks = {
    abCalcExprRealParse,
    abCalcExprRealFormat
};


void abCalcExprRealInit(void)
{
    abCalcRegisterExprType(abCalcExprTypeReal, &gRealCallbacks);
}


abCalcExpr *abCalcExprRealParse(abCalcExpr *expr, char *buffer)
{
    int offset;
    int expOffset = -1;
    int periodOffset = -1;
    int len;
    int numOffset = -1;

    /* First validate */
    if (buffer == NULL)
        return NULL;

    if (expr == NULL)
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
                numOffset = offset;
                break;

            case '.':
                if (periodOffset != -1)
                    return NULL;
                if (expOffset != -1)
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
                numOffset = -1;
                break;

            default:
                return NULL;
        }
    }

    if (numOffset == -1)
        return NULL;
    
    expr->type = abCalcExprTypeReal;
    expr->u.real = atof(buffer);
    return expr;
}


char *abCalcExprRealFormat(abCalcExpr *expr, char *buffer)
{
	abCalcRealType exp;
	abCalcRealType value;
    static char format[16];
    int numDecDigits;
	int periodPos = -1;
	int zerosStart = -1;
	int spaceStart = -1;
	int expPos = -1;
    int len;
    int i;

    if (expr == NULL)
        return NULL;

    if (buffer == NULL)
        return NULL;

    if (expr->type != abCalcExprTypeReal)
        return NULL;

    value = expr->u.real;

	if (value == 0.0) {
		exp = 0.0;
	} else {
		exp = floor(log10(fabs(value)));
	}
	
	if (exp >= 0)
		exp++;
	
	if ((exp > 12) ||
		(exp < -12)) {
		strcpy(format, "%-25.11E");
	} else if (exp <= -2) {
		double shiftedValue = value * 1.0e12;
		if (shiftedValue == floor(shiftedValue)) {
			strcpy(format, "%-18.12f");
		} else {
			strcpy(format, "%-25.11E");
		}
	} else {
		int numDecDigits = (int)(12 - exp);
		if (numDecDigits > 12) {
			numDecDigits = 12;
		}
		sprintf(format, "%%-28.%df", numDecDigits);
	}

    sprintf(buffer, format, value);
    len = strlen(buffer);

	for (i = 0; i < len; i++) {
		switch (buffer[i]) {
			case '.':
				periodPos = i;
				break;

			case '0':
				if (expPos != -1) {
					break;
				}
				if ((periodPos != -1) &&
					(zerosStart == -1)) {
					if (periodPos == i - 1) {
						zerosStart = periodPos;
					} else {
						zerosStart = i;
					}
				}
				break;
			case 'E':
				expPos = i;
				break;
			case ' ':
				spaceStart = i;
				break;
			default:
				if (expPos == -1)
					zerosStart = -1;
				break;
		}
		if (spaceStart != -1)
			break;
	}
	
	if (spaceStart != -1) {
        buffer[spaceStart] = '\0';
        len = spaceStart;
	}
	
	if (zerosStart != -1) {
		if (expPos != -1) {
            memmove(&buffer[zerosStart], &buffer[expPos], len - expPos + 1);
			len = expPos - zerosStart;
        }
		else {
			buffer[zerosStart] = '\0';
        }
	}
	
    return buffer;
}


void abCalcExprRealSet(abCalcExpr *expr, abCalcRealType value)
{
    if (expr == NULL)
        return;

    expr->type = abCalcExprTypeReal;
    expr->u.real = value;
}
