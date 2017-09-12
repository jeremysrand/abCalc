all:  
	make -f nda.mk gen
	make -f nda.mk build
	make -f shell.mk gen
	make -f shell.mk build

gen:
	make -f nda.mk gen
	make -f shell.mk gen

build:
	make -f nda.mk build
	make -f shell.mk build

clean:
	make -f shell.mk clean
	make -f nda.mk clean

execute:
	make -f nda.mk execute
#   make -f shell.mk execute
