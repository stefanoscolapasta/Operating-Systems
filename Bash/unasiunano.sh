n=0

while read RIGA;
	do if (( n%2==0 ));then
		echo $RIGA;
	fi;
	((n++));
done;
