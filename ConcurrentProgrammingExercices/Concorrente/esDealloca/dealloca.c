
typedef struct s_NODO{
	int key;
	double x;
	s_NODO *destra;
	s_NODO *sinistra;
}NODO;

void dealloca_albero(NODO **ppnodo){
		if(destra == NULL && sinistra == NULL){
			free(*ppnodo);
			*ppnodo = NULL;
		} else {
			if((*ppnodo)->destra != NULL){
				dealloca_albero(&((*(*ppnodo)).destra));
			}
			if((*ppnodo)->sinistra != NULL){
				dealloca_albero(&((*ppnodo)->sinistra));
			}	
		}	
} 

void main(){
	NODO *root;
	costruisci_albero(&root);
	usa_albero(root);
	dealloca_albero(&root);
}
