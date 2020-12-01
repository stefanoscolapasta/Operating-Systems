# Makefile per con_trucco.c
# a causa della presenza di pthread
# occorre compilare col flag -D_REENTRANT
# oppure con  -D_THREAD_SAFE 
# oppure con  -D_THREAD_SAFE  
# per usare strerror_r devo anche usare _POSIX_C_SOURCE=200112L

CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: 			con_trucco.exe 

con_trucco.exe: con_trucco.o
				gcc ${CFLAGS} -o con_trucco.exe con_trucco.o ${LIBRARIES}

con_trucco.o: 	con_trucco.c
				gcc ${CFLAGS} -c con_trucco.c 

.PHONY:			clean

clean:
				rm -f con_trucco.o con_trucco.exe 
