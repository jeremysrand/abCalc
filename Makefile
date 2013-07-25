OBJS=abCalc.o abCalcExpr.o abCalcExpReal.o abCalcExprInt.o abCalcStack.o \
    abCalcMode.o abCalcMain.o abCalcOp.o abCalcError.o abCalcOpAdd.o \
    abCalcOpSubtr.o abCalcOpMult.o abCalcOpDiv.o abCalcOpPower.o \
    abCalcOpAnd.o abCalcOpOr.o abCalcOpXor.o abCalcOpNot.o \
    abCalcOpBin.o abCalcOpOct.o abCalcOpDec.o abCalcOpHex.o abCalcOpStws.o \
    abCalcOpRcws.o abCalcOpSl.o abCalcOpRl.o abCalcOpSr.o abCalcOpRr.o \
    abCalcOpAsr.o

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
    abCalcOpAnd.h abCalcOpOr.h abCalcOpXor.h abCalcOpNot.h abCalcOpBin.h \
    abCalcOpOct.h abCalcOpDec.h abCalcOpHex.h abCalcOpStws.h abCalcOpRcws.h \
    abCalcOpSl.h abCalcOpRl.h abCalcOpSr.h abCalcOpRr.h abCalcOpAsr.h
abCalcOpAdd.o: abCalcOp.h abCalcError.h abCalcExpr.h abCalcExpReal.h abCalcExprInt.h abCalcStack.h abCalcOpAdd.h
abCalcOpSubtr.o: abCalcOp.h abCalcError.h abCalcExpr.h abCalcExpReal.h abCalcExprInt.h abCalcStack.h abCalcOpSubtr.h
abCalcOpMult.o: abCalcOp.h abCalcError.h abCalcExpr.h abCalcExpReal.h abCalcExprInt.h abCalcStack.h abCalcOpMult.h
abCalcOpDiv.o: abCalcOp.h abCalcError.h abCalcExpr.h abCalcExpReal.h abCalcExprInt.h abCalcStack.h abCalcOpDiv.h
abCalcOpPower.o: abCalcOp.h abCalcError.h abCalcExpr.h abCalcExpReal.h abCalcStack.h abCalcOpPower.h
abCalcOpAnd.o: abCalcOp.h abCalcError.h abCalcExpr.h abCalcExprInt.h abCalcStack.h abCalcOpAnd.h
abCalcOpOr.o: abCalcOp.h abCalcError.h abCalcExpr.h abCalcExprInt.h abCalcStack.h abCalcOpOr.h
abCalcOpXor.o: abCalcOp.h abCalcError.h abCalcExpr.h abCalcExprInt.h abCalcStack.h abCalcOpXor.h
abCalcOpNot.o: abCalcOp.h abCalcError.h abCalcExpr.h abCalcExprInt.h abCalcStack.h abCalcOpNot.h
abCalcOpBin.o: abCalcOp.h abCalcMode.h abCalcOpBin.h
abCalcOpOct.o: abCalcOp.h abCalcMode.h abCalcOpOct.h
abCalcOpDec.o: abCalcOp.h abCalcMode.h abCalcOpDec.h
abCalcOpHex.o: abCalcOp.h abCalcMode.h abCalcOpHex.h
abCalcOpStws.o: abCalcOp.h abCalcMode.h abCalcStack.h abCalcExpr.h abCalcError.h abCalcOpStws.h
abCalcOpRcws.o: abCalcOp.h abCalcMode.h abCalcStack.h abCalcExpr.h abCalcExpReal.h abCalcOpRcws.h
abCalcOpSl.o: abCalcOp.h abCalcError.h abCalcStack.h abCalcExpr.h abCalcExprInt.h abCalcOpSl.h
abCalcOpRl.o: abCalcOp.h abCalcMode.h abCalcError.h abCalcStack.h abCalcExpr.h abCalcExprInt.h abCalcOpRl.h
abCalcOpSr.o: abCalcOp.h abCalcError.h abCalcStack.h abCalcExpr.h abCalcExprInt.h abCalcOpSr.h
abCalcOpRr.o: abCalcOp.h abCalcMode.h abCalcError.h abCalcStack.h abCalcExpr.h abCalcExprInt.h abCalcOpRr.h
abCalcOpAsr.o: abCalcOp.h abCalcMode.h abCalcError.h abCalcStack.h abCalcExpr.h abCalcExprInt.h abCalcOpAsr.h


$(NAME): $(OBJS)
	cc -o $(NAME) $(OBJS)

clean:
	rm -f $(NAME) $(OBJS)
