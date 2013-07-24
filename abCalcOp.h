/* 
    abCalcOp.h
        By: Jeremy Rand
 */


#ifndef ABCALCOP_H
#define ABCALCOP_H


typedef struct abCalcOp {
    char *name;
    void (*execute)(void);
} abCalcOp;


void abCalcOpInit(void);

void abCalcOpRegister(char *name, void (*execute)(void));

abCalcOp *abCalcOpLookup(char *name);


#endif
