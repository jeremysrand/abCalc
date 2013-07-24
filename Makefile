OBJS=abCalc.o abCalcExpr.o abCalcExprReal.o abCalcExprInt.o abCalcStack.o
NAME=abCalc

all: $(NAME)

$(NAME): $(OBJS)
	cc -o $(NAME) $(OBJS)

clean:
	rm -f $(NAME) $(OBJS)
