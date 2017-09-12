/* 
    abCMode.h
        By: Jeremy Rand
 */


#ifndef ABCMODE_H
#define ABCMODE_H


#include "expr/abCExpr.h"


typedef enum abCalcModeIntBase
{
    abCalcModeIntBaseMin = 0,
    abCalcModeBinBase = 0,
    abCalcModeOctBase,
    abCalcModeDecBase,
    abCalcModeHexBase,

    abCalcModeIntBaseMax
} abCalcModeIntBase;


void abCalcModeInit(void);

abCalcModeIntBase abCalcModeGetBase(void);

void abCalcModeSetBase(abCalcModeIntBase base);

int abCalcModeGetIntWidth(void);

void abCalcModeSetIntWidth(int width);


#endif
