OBJS=abCalc.o abCalcExpr.o abCalcExprReal.o abCalcExprInt.o abCalcStack.o abCalcMode.o abCalcMain.o
NAME=abCalc

all: $(NAME)

abCalcExpr.o: abCalcExpr.h
abCalcExprReal.o: abCalcExpr.h abCalcExprReal.h
abCalcStack.o: abCalcExpr.h abCalcStack.h
abCalcMode.o: abCalcMode.h abCalcExpr.h
abCalcExprInt.o: abCalcExpr.h abCalcMode.h abCalcExprInt.h
abCalc.o: abCalcExpr.h abCalcMode.h abCalcExprReal.h abCalcExprInt.h abCalcStack.h

$(NAME): $(OBJS)
	cc -o $(NAME) $(OBJS)

clean:
	rm -f $(NAME) $(OBJS)
