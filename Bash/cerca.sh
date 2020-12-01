if [[ -d "$1" ]]; then
	find $1 -type f -iname "*$2*"; 
fi; 
