exec {FD}< asterischi.txt
if(( $? == 0 )); then
	while read -u ${FD} A B C D; do
		echo  "$D $C";
	done;
	exec {FD}>&-
fi;
