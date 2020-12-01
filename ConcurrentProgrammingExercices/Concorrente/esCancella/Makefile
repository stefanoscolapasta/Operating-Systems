CFLAGS=gcc -ansi -Wall -Wpedantic -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all:			main.exe

main.exe:		main.o
				${CFLAGS} -o main.exe main.o ${LIBRARIES}

main.o:			main.c
				${CFLAGS} -c main.c

.PHONY:			clean

clean:
				rm -f *.o *.exe
