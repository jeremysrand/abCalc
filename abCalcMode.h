/* 
    abCalcMode.h
        By: Jeremy Rand
 */


#include "abCalcExpr.h"


typedef enum abCalcModeIntBase
{
    abCalcModeIntBaseMin = 0,
    abCalcModeBinBase = 0,
    abCalcModeOctBase,
    abCalcModeDecBase,
    abCalcModeHexBase,

    abCalcModeIntBaseMax
} abCalcModeIntBase;


#define AB_CALC_MODE_MAX_INT_WIDTH ((sizeof(abCalcIntType) * 8))


void abCalcModeInit(void);

abCalcModeIntBase abCalcModeGetBase(void);

void abCalcModeSetBase(abCalcModeIntBase base);

int abCalcModeGetIntWidth(void);

void abCalcModeSetIntWidth(int width);
