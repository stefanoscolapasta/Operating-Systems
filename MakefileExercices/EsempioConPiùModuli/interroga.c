#include <unistd.h>
#include <stdlib.h>		/* serve per la funzione rand */
#include <stdio.h>	
#include <time.h>		/* serve per la funzione time */

/* compilare con -D_BSD_SOURCE  per random */

static int inizializzato=0;

static void inizializza_generatore_numeri_casuali(void)
{
	unsigned int seme;
	
	seme=time(NULL);
	srandom(seme);
}


		/* implementazione */
unsigned int interroga_oracolo(void)
{
	unsigned int risultato;

	/* se non l'ho gia' fatto prima, 
	inizializzo il generatore dei numeri casuali */

	if(inizializzato==0) {
		inizializza_generatore_numeri_casuali();
		inizializzato=1;
	}

	/* genero un numero casuale tra 0 e 299 */
	risultato=random()%300;

	return( (double)risultato);
}
