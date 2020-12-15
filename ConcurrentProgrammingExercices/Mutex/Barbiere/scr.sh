echo "" > primo.txt
for i in `find /usr/include -maxdepth 1 -mindepth 1 -name "*.h"`; do
	RIS=`grep "ifdef" $i | wc -l`
	echo "RISSSSS----> $RIS"
	if ((RIS >= 10)); then
		grep "ifdef" $i | head -n 5 >> primo.txt
	fi
done 
sort primo.txt > FINALE.txt
exit 0
