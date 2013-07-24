OBJS=abCalc.o abCalcExpr.o abCalcExpReal.o abCalcExprInt.o abCalcStack.o \
    abCalcMode.o abCalcMain.o abCalcOp.o abCalcError.o abCalcOpAdd.o \
    abCalcOpSubtr.o abCalcOpMult.o abCalcOpDiv.o abCalcOpPower.o \
    abCalcOpAnd.o abCalcOpOr.o abCalcOpXor.o abCalcOpNot.o

NAME=abCalc

all: $(NAME)

abCalcExpr.o: abCalcExpr.h
abCalcExpReal.o: abCalcExpr.h abCalcExpReal.h
abCalcExprInt.o: abCalcExpr.h abCalcMode.h abCalcExprInt.h
abCalcStack.o: abCalcExpr.h abCalcStack.h abCalcError.h
abCalcMode.o: abCalcMode.h abCalcExpr.h
abCalcError.o: abCalcError.h
abCalc.o: abCalc.h abCalcExpr.h abCalcMode.h abCalcExpReal.h abCalcExprInt.h \
    abCalcStack.h abCalcOp.h abCalcError.h
abCalcMain.o: abCalc.h abCalcStack.h abCalcExpr.h abCalcOp.h abCalcError.h
abCalcOp.o: abCalcOp.h abCalcError.h abCalcExpr.h abCalcStack.h abCalcOpAdd.h \
    abCalcOpSubtr.h abCalcOpMult.h abCalcOpDiv.h abCalcOpPower.h \
    abCalcOpAnd.h abCalcOpOr.h abCalcOpXor.h abCalcOpNot.h
abCalcOpAdd.o: abCalcOp.h abCalcError.h abCalcOpAdd.h
abCalcOpSubtr.o: abCalcOp.h abCalcError.h abCalcOpSubtr.h
abCalcOpMult.o: abCalcOp.h abCalcError.h abCalcOpMult.h
abCalcOpDiv.o: abCalcOp.h abCalcError.h abCalcOpDiv.h
abCalcOpPower.o: abCalcOp.h abCalcError.h abCalcOpPower.h
abCalcOpAnd.o: abCalcOp.h abCalcError.h abCalcOpAnd.h
abCalcOpOr.o: abCalcOp.h abCalcError.h abCalcOpOr.h
abCalcOpXor.o: abCalcOp.h abCalcError.h abCalcOpXor.h
abCalcOpNot.o: abCalcOp.h abCalcError.h abCalcOpNot.h


$(NAME): $(OBJS)
	cc -o $(NAME) $(OBJS)

clean:
	rm -f $(NAME) $(OBJS)
