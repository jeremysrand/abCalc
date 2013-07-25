/* 
    abCExpReal.h
        By: Jeremy Rand
 */


#ifndef ABCEXPREAL_H
#define ABCEXPREAL_H


struct abCalcExpr;

void abCalcExprRealInit(void);

void abCalcExprRealSet(struct abCalcExpr *expr, abCalcRealType value);

#endif
