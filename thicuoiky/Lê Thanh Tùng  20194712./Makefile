CFLAGS =-w -c -Wall
CC =gcc
LIBS = -lm

all: main

main: main.o 
	${CC} -w main.o GraphAPI/graph_jrb.c libfdr/libfdr.a -o main
	rm -f *.o
main.o: main.c
	${CC} ${CFLAGS} main.c

clean:
	rm -f *.o *~ main
