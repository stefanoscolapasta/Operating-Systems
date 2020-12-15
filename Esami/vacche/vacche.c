/* file:  vacche.c */

#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif

/* la   #define _POSIX_C_SOURCE 200112L   e' dentro printerror.h */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE     /* per random e srandom */
#endif


/* messo prima perche' contiene define _POSIX_C_SOURCE */
#include "printerror.h"

#include <unistd.h>   /* exit() etc */
#include <stdlib.h>     /* random  srandom */
#include <stdio.h>
#include <string.h>     /* per strerror_r  and  memset */
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h> /*gettimeofday() struct timeval timeval{} for select()*/
#include <time.h> /* timespec{} for pselect() */
#include <limits.h> /* for OPEN_MAX */
#include <errno.h>
#include <assert.h>
#include <stdint.h>     /* uint64_t intptr_t */
#include <inttypes.h>   /* per PRIiPTR */
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#include "DBGpthread.h"

#define NUMMANGIATOIE 3
#define NUMVACCHE 6
#define SECGIRO 10
#define MINSECMANGIARE 5
#define MAXSECMANGIARE 7
#define SECINTERVALLOTRAINCENDI 15
#define SECDURATAINCENDIO 5

/* dati da proteggere */
int pagliabrucia=0;
int mangiatoieOccupate = 0;
/* variabili per la sincronizzazione */
pthread_mutex_t  mutex;
pthread_mutex_t  paglia;
pthread_cond_t cond;

void attendi( int min, int max) {
	int secrandom=0;
	if( min > max ) return;
	else if ( min == max ) 
		secrandom = min;
	else
		secrandom = min + ( random()%(max-min+1) );
	do {
		/* printf("attendi %i\n", secrandom);fflush(stdout); */
		secrandom=sleep(secrandom);
		if( secrandom>0 ) 
			{ printf("sleep interrupted - continue\n"); fflush(stdout); }
	} while( secrandom>0 );
	return;
}

void *Vacca (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Vacca%" PRIiPTR "",indice);

	/*  da completare  */

	while ( 1 ) {
		int i, secmangiare;

		/* la vacca attende di poter mangiare */
		printf("MUCCA %" PRIiPTR " partita\n", indice);
		DBGpthread_mutex_lock(&paglia, "MUCCA");

		while(mangiatoieOccupate >= 3){
			printf("MUCCA %" PRIiPTR " aspetta ordinatamente in fila si liberi la mangiatoia\n", indice);
			DBGpthread_cond_wait(&cond, &paglia, "MUCCA");
		}
		mangiatoieOccupate++;
		DBGpthread_mutex_unlock(&paglia, "MUCCA");


		/* la vacca mangia */
		printf("vacca %s mangia\n", Plabel);
       		fflush(stdout);
		/* quale e' il tempo in secondi durante il quale la vacca mangia? */
		secmangiare=MINSECMANGIARE + ( random()%(MAXSECMANGIARE-MINSECMANGIARE+1) );

		for(i=0; i<secmangiare; i++){
			attendi(1, 1);
			DBGpthread_mutex_lock(&mutex, "MUCCA");
			if(pagliabrucia==1){
				DBGpthread_mutex_unlock(&mutex, "MUCCA");
				break;
			}
			DBGpthread_mutex_unlock(&mutex, "MUCCA");
		}
		
			/* ogni secondo la vacca guarda se la paglia brucia */

		DBGpthread_mutex_lock(&paglia, "MUCCA");
		mangiatoieOccupate--;
		DBGpthread_cond_signal(&cond, "MUCCA");
		DBGpthread_mutex_unlock(&paglia, "MUCCA");

		/* la vacca libera la mangiatoia */

		/* la vacca fa un giro di 10 secondi */
		attendi( SECGIRO, SECGIRO );
		printf("vacca %s finisce giro\n", Plabel);
       		fflush(stdout);

	}
	pthread_exit(NULL); 
}


void Bovaro (void) 
{ 
	char Plabel[128];

	sprintf(Plabel,"Bovaro");
	while( 1 ) {
		/* attesa 30 sec tra incendi */
		attendi( SECINTERVALLOTRAINCENDI, SECINTERVALLOTRAINCENDI );

		/* bovaro incendia paglia */
		DBGpthread_mutex_lock(&mutex,Plabel); 
		pagliabrucia=1;
		printf("bovaro incendia paglia\n");
        	fflush(stdout);
		DBGpthread_mutex_unlock(&mutex,Plabel); 

		/* durata incendio 3 sec */
		attendi( 3, 3 );

		/* bovaro spegne paglia */
		DBGpthread_mutex_lock(&mutex,Plabel); 
		pagliabrucia=0;
		printf("paglia spenta\n");
        	fflush(stdout);
		DBGpthread_mutex_unlock(&mutex,Plabel); 
	}

	pthread_exit(NULL); 
}


int main ( int argc, char* argv[] ) 
{ 
	pthread_t    th; 
	int  rc;
	uintptr_t i=0;
	int seme;

	seme=time(NULL);
        srandom(seme);

	rc = pthread_mutex_init(&mutex, NULL); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	pagliabrucia=0; /* la paglia non brucia */

	/* INIZIALIZZATE LE VOSTRE ALTRE VARIABILI CONDIVISE / fate voi */

	DBGpthread_mutex_init(&mutex, NULL, "main");
	DBGpthread_mutex_init(&paglia, NULL, "main");
	DBGpthread_cond_init(&cond, NULL, "main");


	/* CREAZIONE PTHREAD */
	for(i=0;i<NUMVACCHE;i++) {
		rc=pthread_create(&th,NULL,Vacca,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	Bovaro();
	pthread_exit(NULL);
	return(0); 
} 
  
