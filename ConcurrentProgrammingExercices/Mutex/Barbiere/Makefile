CFLAGSCONSTRERROR=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE 

LIBRARIES=-lpthread

all: 	 barbiere.exe

barbiere.exe:  barbiere.o DBGpthread.o 
	gcc ${CFLAGS} -o barbiere.exe barbiere.o DBGpthread.o ${LIBRARIES}

barbiere.o: barbiere.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} barbiere.c 

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGSCONSTRERROR} -c DBGpthread.c


.PHONY:	clean

clean:
	-rm -f barbiere.o DBGpthread.o barbiere.exe


