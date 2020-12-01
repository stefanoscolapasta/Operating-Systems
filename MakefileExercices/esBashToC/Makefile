all:	main.exe

main.exe:	main.o variabiliglobali.o
		gcc -ansi -Wall -Wpedantic -o main.exe main.o variabiliglobali.o

main.o:		main.c variabiliglobali.h define.h
		gcc -c -ansi -Wall -Wpedantic main.c

variabiliglobali.o:	variabiliglobali.c
			gcc -c -ansi -Wall -Wpedantic variabiliglobali.c

variabiliglobali.c:define.h
		./creaC.sh

variabiliglobali.h:define.h
		./creaH.sh

.PHONY:			clean

clean:
			rm main.exe *.o


