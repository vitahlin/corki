.PHONY: build clean cleano

build:
	clang -c log_err.c system.c tellwait.c apue.h

cleano:
	-rm -f *.o

clean:
	make -f lib.mk cleano
	-rm -f *.out *.gch