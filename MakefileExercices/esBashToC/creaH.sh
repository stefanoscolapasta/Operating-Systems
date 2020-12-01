#!/bin/bash

touch variabiliglobali.h;

while read A B C; do
	for((i=1;i<=$C;i++));do
		echo -e "extern int var$i;\n" >> variabiliglobali.h
	done;
	echo -e "extern int conta(void);\n" >> variabiliglobali.h
done < define.h
