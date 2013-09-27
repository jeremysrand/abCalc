#
# Makefile
#    By: Jeremy Rand
#

SHELL_NAME=abCalc
NDA_NAME=abCalcNDA

all: $(SHELL_NAME) $(NDA_NAME)

.INCLUDE: "Make.engine"

CFLAGS=-D ABCALC_GSOS

$(SHELL_NAME): $(SHELL_OBJS)
	occ -o $(SHELL_NAME) $(SHELL_OBJS)

$(NDA_NAME): $(NDA_OBJS) $(NDA_NAME).r
	cp -f $(NDA_NAME).r $(NDA_NAME)
	occ -M -o $(NDA_NAME) $(NDA_OBJS) > $(NDA_NAME).map
	chtyp -t nda $(NDA_NAME)

abCMain.o: abCMain.c
	occ $(CFLAGS) -c -o $@ $<

$(NDA_NAME).o: $(NDA_NAME).c
	occ $(CFLAGS) -c -o $@ $<

clean:
	cp -p rm -f $(SHELL_NAME) $(SHELL_OBJS) $(SHELL_NAME).root
	cp -p rm -f $(NDA_NAME) $(NDA_OBJS) $(NDA_NAME).r $(NDA_NAME).root
	cp -p rm -f *.root
	cp -p rm -f *.map
	cp -p rm -f expr/*.root
	cp -p rm -f ops/*.root

fixfiles:
	tr '\\012' '\\015' < abCalcNDA.defs > /tmp/blah
	cp -f /tmp/blah abCalcNDA.defs
	tr '\\012' '\\015' < abCalcNDA.rez > /tmp/blah
	cp -f /tmp/blah abCalcNDA.rez
	chtyp -l CC *.c *.h *.defs
	chtyp -l REZ *.rez
	chtyp -l CC expr/*.c expr/*.h
	chtyp -l CC ops/*.c ops/*.h

%.o: %.c
	occ $(CFLAGS) -r -c -o $@ $<

%.r: %.rez
	occ -o $@ $<
