CFLAGS=-ansi -Wall -Wpedantic
LIBR=-lpthread

all:	piattello.exe

piattello.exe:	piattello.o DBGpthread.o 
				gcc ${CFLAGS} -o piattello.exe piattello.o DBGpthread.o ${LIBR}
		
piattello.o:	piattello.c DBGpthread.h
				gcc -c ${CFLAGS} piattello.c
				
DBGpthread.o:	DBGpthread.c printerror.h
				gcc -c ${CFLAGS} DBGpthread.c		

.PHONY:			clean

clean:
				rm *.o piattello.exe
				
