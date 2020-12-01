#include <stdlib.h>
#include <unistd.h>   /* per sleep */
#include <stdio.h>

/* NOTARE CHE NON HO MESSO IL PROTOTIPO
   DELLA FUNZIONE DoppioDelCoseno
   (e' commentato)
   E NON HO MESSO L'OPZIONE DI COMPILAZIONE -Wall
*/
extern double DoppioDelCoseno( double x );


int main(void)
{
	double ris;

	ris = DoppioDelCoseno( 0.1 ); 
	printf( "ris = %f \n", ris );

	return(0);
}


