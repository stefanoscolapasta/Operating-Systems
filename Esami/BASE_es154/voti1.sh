while read matricola voto altro; do
	ris=`cat esame2.txt | grep $matricola`
	if [[ -z $ris ]] ; then
		echo "$matricola $voto"
	else
		echo $ris
	fi
done < esame1.txt
