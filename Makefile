OBJS=abCalc.o abCalcExpr.o abCalcExprReal.o abCalcExprInt.o abCalcStack.o \
    abCalcMode.o abCalcMain.o abCalcOp.o abCalcOpAdd.o abCalcError.o

NAME=abCalc

all: $(NAME)

abCalcExpr.o: abCalcExpr.h
abCalcExprReal.o: abCalcExpr.h abCalcExprReal.h
abCalcStack.o: abCalcExpr.h abCalcStack.h abCalcError.h
abCalcMode.o: abCalcMode.h abCalcExpr.h
abCalcExprInt.o: abCalcExpr.h abCalcMode.h abCalcExprInt.h
abCalc.o: abCalc.h abCalcExpr.h abCalcMode.h abCalcExprReal.h abCalcExprInt.h \
         abCalcStack.h abCalcOp.h abCalcError.h
abCalcMain.o: abCalc.h abCalcStack.h abCalcExpr.h abCalcOp.h abCalcError.h
abCalcOp.o: abCalcOp.h abCalcOpAdd.h
abCalcOpAdd.o: abCalcOp.h abCalcOpAdd.h
abCalcError.o: abCalcError.h

CFLAGS=-g

$(NAME): $(OBJS)
	cc -o $(NAME) $(OBJS)

clean:
	rm -f $(NAME) $(OBJS)
