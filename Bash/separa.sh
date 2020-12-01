IFS=":";
OUT=`echo $PATH`
echo $OUT;
IFS=" ";
for i in $OUT; do
	echo "$i ${#i}";
done; 
