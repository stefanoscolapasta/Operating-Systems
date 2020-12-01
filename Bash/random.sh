N=0;

while (( $RANDOM%10 != 2 )); do
	((N++));
done;
echo $N
