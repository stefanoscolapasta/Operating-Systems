/* file:  barbiere.c 
*/ 

#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif


#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>	/* uint64_t */
#include <sys/time.h>	/* gettimeofday()    struct timeval */
#include <pthread.h> 
#include "printerror.h"
#include "DBGpthread.h"

#define NUMSEDIE 5
#define NUMCLIENTI 50

/* nessuna variabili da proteggere */
/* variabili per la sincronizzazione */
int numclientiincoda=0;
pthread_mutex_t  mutex;
pthread_cond_t   condBarbiereLibero; 
pthread_cond_t   condArrivoClienti; 

void *barbiere (void *arg) 
{ 
	char Blabel[128];
	char Blabelsignal[128];
	int indice;

	indice=*((int*)arg);
	free(arg);
	sprintf(Blabel,"B%d",indice);
	sprintf(Blabelsignal,"B%d->C",indice);

	
	while(1) {

		/* barbiere controlla se c'e' qualcun altro in coda */
		/* prendo la mutua esclusione */
		DBGpthread_mutex_lock(&mutex,Blabel); 

		if ( numclientiincoda <= 0 ) 
			/* il barbiere DORME */
			DBGpthread_cond_wait( &condArrivoClienti, &mutex, Blabel );

		/* c'e' qualche cliente in coda, ne risveglio 1 */
		DBGpthread_cond_signal( &condBarbiereLibero, Blabel );
		/* un cliente esce dalla coda e va nella poltrona del barbiere */
		
		/* rilascio mutua esclusione */
		DBGpthread_mutex_unlock(&mutex,Blabel); 

		/* barbiere serve il cliente */
		printf("barbiere %s serve cliente \n", Blabel ); 
		fflush(stdout);
		/* il barbiere lavora sul cliente per 1/2 di sec piu o meno */
		DBGnanosleep( 500000000, Blabel );

		/* barbiere finisce di servire il cliente */
		printf("barbiere %s finisce il cliente \n", Blabel ); 
		fflush(stdout);
	}
	pthread_exit(NULL); 
} 

void *cliente (void *arg) 
{ 
	char Clabel[128];
	char Clabelsignal[128];
	int indice;

	indice=*((int*)arg);
	free(arg);
	sprintf(Clabel,"C%d",indice);
	sprintf(Clabelsignal,"C%d->B",indice);

	
	while(1) {

		/* il cliente aspetta qualche giorno = 1/2 sec e poi va dal barbiere */
		DBGnanosleep( 500000000, Clabel );

		/* cliente controlla se c'e' qualcun altro in coda */
		/* prendo la mutua esclusione */
		DBGpthread_mutex_lock(&mutex,Clabel); 

		/* se non ci sono sedie libere me ne vado incazzato  %@!$&^ */
		if ( numclientiincoda >= NUMSEDIE )  {
			DBGpthread_mutex_unlock(&mutex,Clabel); 
		}
		else {

			/* ci sono sedie libere, mi siedo */
			numclientiincoda++;
		
			if ( numclientiincoda <= 1 ) 
				/* ci sono solo io e il barbiere DORME, devo svegliarlo */
				DBGpthread_cond_signal( &condArrivoClienti, Clabel );

			/* aspetto un assenso dal barbiere per andare alla poltrona */
			DBGpthread_cond_wait( &condBarbiereLibero, &mutex, Clabel );

			/* io cliente esco dalla coda e vado nella poltrona del barbiere */
			numclientiincoda--;

			/* rilascio mutua esclusione */
			DBGpthread_mutex_unlock(&mutex,Clabel); 

			/* il barbiere lavora */
			printf("il cliente %s viene servito\n", Clabel ); 
			fflush(stdout);

			/* il barbiere finisce lavoro e il cliente se ne va */
			printf("il cliente %s se ne va \n", Clabel ); 
			fflush(stdout);
		}
	}
	pthread_exit(NULL); 
} 

int main (int argc, char* argv[] ) 
{ 
	pthread_t    th; 
	int  rc, i, *intptr;

	rc = pthread_cond_init( &condBarbiereLibero , NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init( &condArrivoClienti , NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_mutex_init( &mutex, NULL); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	numclientiincoda=0;
	
	/* lancio il barbiere */
	intptr=malloc(sizeof(int));
	if( !intptr ) { printf("malloc failed\n");exit(1); }
	*intptr=0; /* un solo barbiere */
	rc=pthread_create( &th,NULL,barbiere,(void*)intptr); 
	if(rc) PrintERROR_andExit(rc,"pthread_create failed");

	/* lancio i clienti */
	for(i=0;i<NUMCLIENTI;i++) {
		intptr=malloc(sizeof(int));
		if( !intptr ) { printf("malloc failed\n");exit(1); }
		*intptr=i;
		rc=pthread_create( &th,NULL,cliente,(void*)intptr); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	pthread_exit(NULL); 

	return(0); 
} 
  
  
  
