NAME=abCalc

all: $(NAME)

.INCLUDE: "Make.engine"

$(NAME): fixtype $(OBJS)
	occ -o $(NAME) $(OBJS)

clean:
	cp -p rm -f $(NAME) $(OBJS) $(NAME).r $(NAME).root
	cp -p rm -f *.root
	cp -p rm -f expr/*.root
	cp -p rm -f ops/*.root

fixtype:
	chtyp -l CC *.c *.h
	chtyp -l CC expr/*.c expr/*.h
	chtyp -l CC ops/*.c ops/*.h

%.o: %.c
	occ -c $<
