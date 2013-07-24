/* 
    abCalcExpr.h
        By: Jeremy Rand
 */


typedef enum abCalcExprType {
    abCalcExprTypeReal,
    abCalcExprTypeInt
} abCalcExprType;


typedef double abCalcRealType;
typedef long abCalcIntType;


typedef struct abCalcExpr {
    abCalcExprType type;
    union {
        abCalcRealType real;
        abCalcIntType integer;
    } u;
} abCalcExpr;


typedef struct abCalcExprCallbacks {
    abCalcExpr * (*parseExpression)(abCalcExpr *expr, char *buffer);
} abCalcExprCallbacks;
