/* 
    abCExpr.h
        By: Jeremy Rand
 */


#ifndef ABCEXPR_H
#define ABCEXPR_H


typedef enum abCalcExprType {
    abCalcExprTypeMin = 0,
    abCalcExprTypeReal = 0,
    abCalcExprTypeInt,

    abCalcExprTypeMax
} abCalcExprType;


typedef double abCalcRealType;
typedef unsigned long abCalcIntType;


#define AB_CALC_EXPR_MAX_INT_WIDTH ((sizeof(abCalcIntType) * 8))

#define AB_CALC_EXPR_STRING_MAX (AB_CALC_EXPR_MAX_INT_WIDTH + 8)


typedef struct abCalcExpr {
    abCalcExprType type;
    union {
        abCalcRealType real;
        abCalcIntType integer;
    } u;
} abCalcExpr;


typedef struct abCalcExprCallbacks {
    abCalcExpr * (*parseExpr)(abCalcExpr *expr, char *buffer);
    char * (*formatExpr)(abCalcExpr *expr, char *buffer);
} abCalcExprCallbacks;


void abCalcExprInit(void);
void abCalcRegisterExprType(abCalcExprType type, abCalcExprCallbacks *callbacks);

abCalcExpr *abCalcParseExpr(abCalcExpr *expr, char *buffer);
char *abCalcFormatExpr(abCalcExpr *expr, char *buffer);


#endif
