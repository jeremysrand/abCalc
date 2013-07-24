/* 
    abCalcError.h
        By: Jeremy Rand
 */


#ifndef ABCALCERROR_H
#define ABCALCERROR_H


typedef enum abCalcErrorType {
    abCalcErrorTypeMin = 0,
    abCalcNoError,
    abCalcSyntaxError,
    abCalcBadArgTypeError,
    abCalcBadArgValueError,
    abCalcTooFewArgsError,
    abCalcStackFullError,
    abCalcInfiniteResultError,
    abCalcComplexResultError,

    abCalcErrorTypeMax
} abCalcErrorType;


void abCalcErrorInit(void);

void abCalcRaiseError(abCalcErrorType type, char *opName);

char *abCalcGetError(void);

void abCalcClearError(void);


#endif
