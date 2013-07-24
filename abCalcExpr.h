/* 
    abCalcExpr.h
        By: Jeremy Rand
 */


typedef enum abCalcExprType {
    abCalcExprTypeMin = 0,
    abCalcExprTypeReal = 0,
    abCalcExprTypeInt,

    abCalcExprTypeMax
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
    abCalcExpr * (*parseExpr)(abCalcExpr *expr, char *buffer);
    char * (*formatExpr)(abCalcExpr *expr, char *buffer);
} abCalcExprCallbacks;


void abCalcExprInit(void);
void abCalcRegisterExprType(abCalcExprType type, abCalcExprCallbacks *callbacks);

abCalcExpr *abCalcParseExpr(abCalcExpr *expr, char *buffer);
char *abCalcFormatExpr(abCalcExpr *expr, char *buffer);
