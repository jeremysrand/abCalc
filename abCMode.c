/* 
    abCMode.c
        By: Jeremy Rand
 */


#include "abCMode.h"



static abCalcModeIntBase gBase = abCalcModeDecBase;
static int gIntWidth = AB_CALC_EXPR_MAX_INT_WIDTH;


void abCalcModeInit(void)
{
}


abCalcModeIntBase abCalcModeGetBase(void)
{
    return gBase;
}


void abCalcModeSetBase(abCalcModeIntBase base)
{
    if ((base >= abCalcModeIntBaseMin) &&
        (base < abCalcModeIntBaseMax)) {
        gBase = base;
    }
}


int abCalcModeGetIntWidth(void)
{
    return gIntWidth;
}


void abCalcModeSetIntWidth(int width)
{
    if ((width > 0) &&
        (width <= AB_CALC_EXPR_MAX_INT_WIDTH)) {
        gIntWidth = width;
    }
}
