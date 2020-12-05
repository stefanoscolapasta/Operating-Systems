CLFAGS=-ansi -Wall -Wpedantic -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LIBR=-lpthread

all: 			main.exe

main.exe:		main.o
				gcc ${CFLAGS} -o main.exe main.o ${LIBR}
				
main.o:			main.c
				gcc -c ${CFLAGS} main.c
				
.PHONY:			clean

clean:
				rm *.o *.exe
				
