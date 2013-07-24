OBJS=abCalc.o abCalcExpr.o abCalcExprReal.o abCalcExprInt.o abCalcStack.o
NAME=abCalc

all: $(NAME)

abCalcExpr.o: abCalcExpr.h
abCalcExprReal.o: abCalcExpr.h
abCalcStack.o: abCalcExpr.h abCalcStack.h

$(NAME): $(OBJS)
	cc -o $(NAME) $(OBJS)

clean:
	rm -f $(NAME) $(OBJS)
