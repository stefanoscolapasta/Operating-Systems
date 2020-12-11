./figlio.sh $$ &

ricevutoSIGUSR2(){
	exit 1;
}

trap ricevutoSIGUSR2 SIGUSR2

while true; do
	sleep 1
	echo  "PADRE DICE: $$"
done
