# Makefile per mutex e CondVar* 
# a causa della presenza di strerror_r in printerror.h
# occorre compilare definendo il simbolo -D_POSIX_C_SOURCE=200112L
# ed e' bene compilare con uno dei due simboli  _THREAD_SAFE o _REENTRANT
# I due simboli sono equivalenti, per ricordare che esistono entrambi,
# nell'esempio li definisco entrambi, ma ne basterebbe uno solo.

CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: 	mutex.exe CondVarBroadcast.exe CondVarSignal.exe es1_banche.exe

mutex.exe: mutex.o
	gcc ${CFLAGS} -o mutex.exe mutex.o ${LIBRARIES}

mutex.o: mutex.c printerror.h
	gcc ${CFLAGS} -c mutex.c

CondVarBroadcast.exe: CondVarBroadcast.o
	gcc ${CFLAGS} -o CondVarBroadcast.exe CondVarBroadcast.o ${LIBRARIES}

CondVarBroadcast.o: CondVarBroadcast.c printerror.h
	gcc ${CFLAGS} -c CondVarBroadcast.c 

CondVarSignal.exe: CondVarSignal.o
	gcc ${CFLAGS} -o CondVarSignal.exe CondVarSignal.o ${LIBRARIES}

CondVarSignal.o: CondVarSignal.c printerror.h
	gcc ${CFLAGS} -c CondVarSignal.c 
	
es1_banche.exe: es1_banche.o
	gcc ${CFLAGS} -o es1_banche.exe es1_banche.o ${LIBRARIES}

es1_banche.o: es1_banche.c printerror.h
	gcc ${CFLAGS} -c es1_banche.c 

.PHONY:	clean

clean:
	rm -f mutex.o mutex.exe CondVarBroadcast.o CondVarBroadcast.exe CondVarSignal.o CondVarSignal.exe es1_banche.exe es1_banche.o

