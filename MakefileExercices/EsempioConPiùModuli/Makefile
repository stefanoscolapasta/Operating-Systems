CFLAGS=-ansi -Wall -Wpedantic 

all: oracolo.exe

oracolo.exe:	oracolo.o interroga.o
				gcc ${CFLAGS} -o oracolo.exe oracolo.o interroga.o 
				
oracolo.o:		oracolo.c interroga.h
				gcc -c ${CFLAGS} oracolo.c interroga.h 

interroga.o:	interroga.c
				gcc -c ${CFLAGS} interroga.c -D_BSD_SOURCE
				
.PHONY:			clean

clean:
				-rm *.o *.exe
