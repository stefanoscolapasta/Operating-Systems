#!/bin/bash

touch variabiliglobali.c;

while read A B C; do
	for((i=1;i<=$C;i++));do
		echo -e "int var$i=$i;\n" >> variabiliglobali.c
	done;
	echo -e "int conta(void){\n" >> variabiliglobali.c
	echo -e "int i=0;\n" >> variabiliglobali.c
	echo "i=var1" >> variabiliglobali.c
	for((i=2;i<=$C;i++));do
		 echo "+var$i" >> variabiliglobali.c
	done
	echo -e ";\n" >> variabiliglobali.c
	echo "return i;}" >> variabiliglobali.c
done < define.h
