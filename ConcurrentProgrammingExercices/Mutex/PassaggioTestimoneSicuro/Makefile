CFLAGSCONSTRERROR=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE 

LIBRARIES=-lpthread

all: 	 PassaggioSicuroDiTestimone.exe

PassaggioSicuroDiTestimone.exe:  PassaggioSicuroDiTestimone.o DBGpthread.o 
	gcc ${CFLAGS} -o PassaggioSicuroDiTestimone.exe PassaggioSicuroDiTestimone.o DBGpthread.o ${LIBRARIES}

PassaggioSicuroDiTestimone.o: PassaggioSicuroDiTestimone.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} PassaggioSicuroDiTestimone.c 

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGSCONSTRERROR} -c DBGpthread.c  


.PHONY:	clean

clean:
	-rm -f PassaggioSicuroDiTestimone.o DBGpthread.o PassaggioSicuroDiTestimone.exe


