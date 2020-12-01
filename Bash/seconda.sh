exec {FD}< $1;
OUT="";
if (( $? == 0 )); then
	while read -u ${FD} A B C; do
		OUT+=$B;
	done;
fi;
echo $OUT;
