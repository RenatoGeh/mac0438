/*******************************************************************/
/** MAC 438 - Programação Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Primeiro Exercício-Programa                                   **/
/** Arquivo: Makefile                                             **/
/**                                                               **/
/** Renato Lui Geh - 8536030                                      **/
/**                                                               **/
/** 04/04/2016                                                    **/
/*******************************************************************/


CFLAGS = -std=c99 -pedantic -Wall -Wno-unused-result
LIBS = -lm
DEBUG = false

ifeq ($(DEBUG), true)
	CFLAGS += -g
else
	CFLAGS += -O2
endif

DEPS = utils.o sort.o fib.o buffon.o integ.o

all: run

run: main.o $(DEPS)
	gcc $^ -o $@ $(LIBS)

main.o: main.c
	gcc -c $(CFLAGS) $^

utils.o: utils.c utils.h
	gcc -c $(CFLAGS) $^

sort.o: sort.c sort.h
	gcc -c $(CFLAGS) $^

fib.o: fib.c fib.h
	gcc -c $(CFLAGS) $^

buffon.o: buffon.c buffon.h
	gcc -c $(CFLAGS) $^

integ.o: integ.c integ.h
	gcc -c $(CFLAGS) $^

.PHONY: clean
clean:
	rm *.out *.gch *.o run

