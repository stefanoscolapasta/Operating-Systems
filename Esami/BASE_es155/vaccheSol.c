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
int mangiatoie[NUMMANGIATOIE]; /* 0 libera, 1 occupata */
int pagliabrucia=0;

/* variabili per la sincronizzazione */
pthread_mutex_t  mutex;
pthread_cond_t   condSvegliaVacche;


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

/* eseguire in mutua esclusione. Restituisce indice mangiatoia libera oppure -1 */
int mangiatoialibera(void) {
	int i;
	for(i=0;i<NUMMANGIATOIE;i++)
		if ( mangiatoie[i]==0 )
			return( i );
	return( -1 );
}


void *Vacca (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Vacca%" PRIiPTR "",indice);

	/*  da completare  */

	while ( 1 ) {
		int indicemangiatoia, i, secmangiare, esci=0;

		/* la vacca prova a mangiare */
		DBGpthread_mutex_lock(&mutex,Plabel); 
		while ( (indicemangiatoia=mangiatoialibera()) < 0 ) {
			printf("vacca %s attende posto libero \n", Plabel);
	        	fflush(stdout);
			DBGpthread_cond_wait(&condSvegliaVacche,&mutex,Plabel);
		}
		mangiatoie[indicemangiatoia]=1;
		printf("vacca %s mangia in mangiatoia %i\n", Plabel, indicemangiatoia);
       		fflush(stdout);
		DBGpthread_mutex_unlock(&mutex,Plabel); 

		secmangiare=MINSECMANGIARE + ( random()%(MAXSECMANGIARE-MINSECMANGIARE+1) );
		for(i=0;i<secmangiare && esci==0;i++) {
			attendi( 1, 1 );

			/* ogni secondo la vacca guarda se la paglia brucia */
			DBGpthread_mutex_lock(&mutex,Plabel); 
			if(pagliabrucia==1) {
				esci=1;
				printf("vacca %s azzz, la paglia brucia ....  vvvviaa\n", Plabel);
	        		fflush(stdout);
			}
			DBGpthread_mutex_unlock(&mutex,Plabel); 
		}

		DBGpthread_mutex_lock(&mutex,Plabel); 
		/* libero mangiatoia */
		mangiatoie[indicemangiatoia]=0;
		printf("vacca %s lascia mangiatoia %i\n", Plabel, indicemangiatoia);
       		fflush(stdout);
		/* sveglio una vacca in attesa di mangiare */
		DBGpthread_cond_signal(&condSvegliaVacche,Plabel);
		DBGpthread_mutex_unlock(&mutex,Plabel); 

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
		attendi( SECDURATAINCENDIO, SECDURATAINCENDIO );

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

	/* INIZIALIZZATE LE VOSTRE VARIABILI CONDIVISE / fate voi */

	rc = pthread_mutex_init(&mutex, NULL); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");
	rc = pthread_cond_init(&condSvegliaVacche, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");

	for(i=0;i<NUMMANGIATOIE;i++) mangiatoie[i]=0; /* mangiatoia libera */
	pagliabrucia=0; /* la paglia non brucia */

	/* CREAZIONE PTHREAD */
	for(i=0;i<NUMVACCHE;i++) {
		rc=pthread_create(&th,NULL,Vacca,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	Bovaro();

	return(0); 
} 
  
