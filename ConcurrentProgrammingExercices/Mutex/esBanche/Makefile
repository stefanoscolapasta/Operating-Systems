CFLAGSCONSTRERROR=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE 

LIBR=-lpthread

all:			banche.exe

banche.exe:		banche.o DBGpthread.o 
				gcc ${CFLAGS} -o banche.exe banche.o DBGpthread.o ${LIBR}
		
banche.o:		banche.c DBGpthread.h
				gcc ${CFLAGS} -c banche.c
				
DBGpthread.o:	DBGpthread.c printerror.h
				gcc ${CFLAGSCONSTRERROR} -c DBGpthread.c		

.PHONY:			clean

clean:
				rm *.o banche.exe
				
