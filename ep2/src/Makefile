CFLAGS = -pedantic -Wall -Wno-unused-result
LIBS = -lm -lpthread

DEPS = utils.o student.o guard.o room.o lock.o queue.o

all: ep2

debug: CFLAGS += -g -D DEBUG=1
debug: ep2

ep2: main.o $(DEPS)
	gcc $^ -o $@ $(LIBS) $(POSIX)

main.o: main.c
	gcc -c $(CFLAGS) $^

utils.o: utils.c utils.h
	gcc -c $(CFLAGS) $^

student.o: student.c student.h room.h utils.h
	gcc -c $(CFLAGS) $^

guard.o: guard.c guard.h room.h
	gcc -c $(CFLAGS) $^

room.o: room.c room.h student.h
	gcc -c $(CFLAGS) $^

lock.o: lock.c lock.h
	gcc -c $(CFLAGS) $^

queue.o: queue.c queue.h
	gcc -c $(CFLAGS) $^

.PHONY: clean
clean:
	rm *.out *.gch *.o run

