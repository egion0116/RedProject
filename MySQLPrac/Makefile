CC=gcc
CFLAGS=-g -Wall `mysql_config --cflags`
OBJS=Prac.o
TARGET=Prac

all: ${TARGET}

clear:
	rm -f *.o
	rm -f ${TARGET}

${TARGET} : ${OBJS}
	gcc -o $@ $^ `mysql_config --libs`

Prac.o : Prac.c stdfx.h