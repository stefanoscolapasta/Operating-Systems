#include <stdlib.h>
#include <unistd.h> 
#include <stdio.h>

#include <math.h>

double DoppioDelCoseno( double x )
{
	double risultato;

	risultato = 2*cos( x ); 
	printf( "DoppioDelCoseno calcola %f \n", risultato );

	return(risultato);
}


