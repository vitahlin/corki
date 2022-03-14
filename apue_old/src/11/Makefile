.PHONY: buildall clean cleano

cleano:
	cd ../lib && $(MAKE) -f lib.mk cleano
	-rm -f *.o
clean:
	cd ../lib && $(MAKE) -f lib.mk clean
	-rm -f *.o *.out

LIB_OBJ= ../lib/log_err.o ../lib/system.o ../lib/tellwait.o 

CC = clang
C_FLAGS = -g -Wall
INCLUDE = 
LIBS = 

C_SRC := $(wildcard *.c)
OBJ_FILES := $(patsubst %.c,%.o,$(C_SRC))
OUT_FILES := $(patsubst %.c,%.out,$(C_SRC))
$(OUT_FILES):$(OBJ_FILES)
	${CC} ${CFLAGS} -o $@ $(LIB_OBJ) $*.o
build_obj:$(OBJ_FILES) 
build_out:$(OUT_FILES)

buildall:
	make clean
	cd ../lib && $(MAKE) -f lib.mk
	make build_obj 
	make build_out