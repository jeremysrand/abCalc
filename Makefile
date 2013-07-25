NAME=abCalc

all: $(NAME)

.INCLUDE: "Make.engine"

$(NAME): $(OBJS)
	occ -o $(NAME) $(OBJS)

clean:
	cp -p rm -f $(NAME) $(OBJS) $(NAME).r $(NAME).root

%.o: %.c
	chtyp -l CC $<
	occ -c $<
