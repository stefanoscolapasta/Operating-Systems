/* macro_in_piu_righe.c  */

#include <unistd.h>
#include <stdlib.h>		/* serve per la funzione rand */
#include <stdio.h>

/* NB: il corpo della macro finirebbe alla fine della riga,
   per farla continuare alla riga successiva devo mettere
   un backslash  \ come ultimo carattere della riga.
   L'ultima riga percio' non necessita del backslash in fondo.
*/
 
#ifndef SALUTAaCASO
	#define SALUTAaCASO 5
#endif

int main(void) {

	printf( "inizio\n" );

	printf("%d\n", SALUTAaCASO);

	printf( "fine\n" );
	return(0);
}


