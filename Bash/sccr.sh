(head -n 5 /usr/include/stdio.h | tail -n 3;
 tail -n 4 /usr/include/stdio.h | cut -b -3) | ( read A; read B; echo "$B"; echo "$A" ; read C &> /dev/null;
 while read C; do echo ${#C}; done)
