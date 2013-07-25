/* 
    abCOp.h
        By: Jeremy Rand
 */


#ifndef ABCOP_H
#define ABCOP_H


#define AB_CALC_OP_ONE_ARG(opName)                       \
    abCalcExpr *expr;                                    \
    if (abCalcStackNumItems() < 1) {                     \
        abCalcRaiseError(abCalcTooFewArgsError, opName); \
        return;                                          \
    }                                                    \
    expr = abCalcStackExprAt(0);

#define AB_CALC_OP_TWO_ARGS(opName)                      \
    abCalcExpr *expr1, *expr2;                           \
    if (abCalcStackNumItems() < 2) {                     \
        abCalcRaiseError(abCalcTooFewArgsError, opName); \
        return;                                          \
    }                                                    \
    expr1 = abCalcStackExprAt(0);                        \
    expr2 = abCalcStackExprAt(1);

typedef struct abCalcOp {
    char *name;
    void (*execute)(void);
} abCalcOp;


void abCalcOpInit(void);

void abCalcOpRegister(char *name, void (*execute)(void));

abCalcOp *abCalcOpLookup(char *name);


#endif
