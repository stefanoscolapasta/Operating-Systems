OUT=`./lanciaeprendi.sh`;
for i in $OUT; do
	kill -9 $i;
done;
