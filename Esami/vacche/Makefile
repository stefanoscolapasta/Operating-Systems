CFLAGS=-ansi -Wall -Wpedantic -D_THREAD_SAFE -D_POSIX_C_SOURCE -D_BSD_SOURCE
LIBS=-lpthread

all:	vacche.exe

vacche.exe:	vacche.o DBGpthread.o
			gcc ${CFLAGS} -o vacche.exe vacche.o DBGpthread.o ${LIBS}

vacche.o:	vacche.c DBGpthread.h
			gcc -c ${CFLAGS} vacche.c 

DBGpthread.o:	DBGpthread.c printerror.h
				gcc -c ${CFLAGS} DBGpthread.c 

.PHONY:			clear

clear:
				rm *.o vacche.exe