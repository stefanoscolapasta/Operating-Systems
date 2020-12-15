# i voti della seconda prova li devo mettere tutti nello standard output
cat esame2.txt ;
# poi devo mettere nello standard output i voti della prima prova
# ottenuti dagli studenti che non hanno un voto nella seconda prova
while read matr voto1 ; do 
	OUT=`grep $matr esame2.txt` ; 
	if [[ $OUT == "" ]] ; 
		then echo $matr $voto1 ; 
	fi ; 
done    < esame1.txt

