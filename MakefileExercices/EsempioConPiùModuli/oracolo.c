#include <stdlib.h>
#include <unistd.h>   /* per sleep */
#include <stdio.h>

#include "interroga.h"



void visualizza_domanda1(void);			/* prototipo di funzione implementata in questo stesso modulo */
void visualizza_risposta1(unsigned int valore);	/* prototipo di funzione implementata in questo stesso modulo */
void visualizza_domanda2(void);			/* prototipo di funzione implementata in questo stesso modulo */
void visualizza_risposta2(unsigned int valore);	/* prototipo di funzione implementata in questo stesso modulo */


int main(void)			/* la funzione principale del programma */
{
	unsigned int risposta;		/* una variabile locale della funzione main */


	visualizza_domanda1();		/* la chiamata (invocazione) della funzione visualizza_domanda1 */
	risposta=interroga_oracolo();	/* la chiamata (invocazione) della funzione interroga_oracolo */
	visualizza_risposta1(risposta);	/* la chiamata (invocazione) della funzione interpreta_visualizza_risposta1 */

	sleep(1);
	printf("\nmumble mumble ...\n\n");
	sleep(2);

	visualizza_domanda2();		/* la chiamata (invocazione) della funzione visualizza_domanda2 */
	risposta=interroga_oracolo();	/* la chiamata (invocazione) della funzione interroga_oracolo */
	visualizza_risposta2(risposta);	/* la chiamata (invocazione) della funzione interpreta_visualizza_risposta2 */


	return(1);
}



void visualizza_domanda1(void)    /* implementazione della funzione visualizza_domanda */
{
	printf(  "Ma quanto si e' rincoglionito il Ghini ??? \n\n" );
}


void visualizza_risposta1(unsigned int risposta)    /* implementazione della funzione visualizza_risposta */
{
	int i;

	for( i=0; i<3; i++) {
		sleep(1);
		printf(  "." );
		fflush(stdout);
	}
	printf( "\n" );
	

	if(risposta<10)
		printf(  "Abbastanza, ma prova a nasconderlo \n\n"   );
	else if(risposta<100)
		printf(  "Poveretto, ormai parla solo in C \n"   );
	else if(risposta<200)
		printf(  "Completamente andato \n"   );
	else 
		printf(  "Non e' peggiorato, Non ha MAI capito un ca*** !! \n\n"   );

}

void visualizza_domanda2(void)    /* implementazione della funzione visualizza_domanda */
{
	printf(  "Come morira' il Ghini ??? \n\n "   );
}


void visualizza_risposta2(unsigned int risposta)    /* implementazione della funzione visualizza_risposta */
{
	int i;

	for( i=0; i<3; i++) {
		sleep(1);
		printf(  "." );
		fflush(stdout);
	}
	printf( "\n" );
	

	if(risposta<10)
		printf(  "Stroncato da un infarto dopo una devastante notte di sesso :-)\n\n"   );
	else if(risposta<80)
		printf(  "Schiantandosi in discesa contro un camion di letame\n"   );
	else if(risposta<140)
		printf(  "Sbranato da un pastore maremmano sullo strappo di Ciola Araldi\n"   );
	else 
		printf(  "Impiccato dai suoi studenti!! \n\n"   );

}

