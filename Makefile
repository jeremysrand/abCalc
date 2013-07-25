#
# Makefile
#    By: Jeremy Rand
#

SHELL_NAME=abCalc
NDA_NAME=abCalcNDA

all: $(SHELL_NAME) $(NDA_NAME)

.INCLUDE: "Make.engine"

CFLAGS=-D ABCALC_GSOS

$(SHELL_NAME): fixtype $(SHELL_OBJS)
	occ -o $(SHELL_NAME) $(SHELL_OBJS)

$(NDA_NAME): fixtype $(NDA_OBJS) $(NDA_NAME).r
	cp $(NDA_NAME).r $(NDA_NAME)
	occ -o $(NDA_NAME) $(NDA_OBJS)
	chtyp -t nda $(NDA_NAME)

clean:
	cp -p rm -f $(SHELL_NAME) $(SHELL_OBJS) $(SHELL_NAME).root
	cp -p rm -f $(NDA_NAME) $(NDA_OBJS) $(NDA_NAME).r $(NDA_NAME).root
	cp -p rm -f *.root
	cp -p rm -f expr/*.root
	cp -p rm -f ops/*.root

fixtype:
	chtyp -l CC *.c *.h
	chtyp -l CC expr/*.c expr/*.h
	chtyp -l CC ops/*.c ops/*.h

%.o: %.c
	occ $(CFLAGS) -c $<

%.r: %.rez
	compile $< keep=$@
