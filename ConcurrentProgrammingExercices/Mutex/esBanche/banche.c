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
#include <time.h>
#include <assert.h>
#include <stdint.h>     /* uint64_t intptr_t */
#include <inttypes.h>   /* per PRIiPTR */
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#include "DBGpthread.h"

#define NUMBANCHE 3
#define NUMDEP 5
#define NUMPRELIEVI 4
#define TEMPOATTESA 100000
#define SLEEPBANCADIITALIA 30

/* dati da proteggere */
int saldoBanca[NUMBANCHE];
int numOperazioniPerBanca[NUMBANCHE];

/* variabili per la sincronizzazione */
pthread_mutex_t  mutex;

void *Depositi (void *arg) 
{ 
	char Plabel[128];
	intptr_t indiceBanca;

	indiceBanca=(intptr_t)arg;
	sprintf(Plabel,"Depositi banca num");

	/*  da completare  */

	while ( 1 ) {   
		DBGpthread_mutex_lock(&mutex, Plabel);
        printf("Thread DEPOSITI di banca %" PRIiPTR " prende mutex\n", indiceBanca);
        saldoBanca[indiceBanca] += 10;
        numOperazioniPerBanca[indiceBanca]++;
        printf("saldoBanca[%" PRIiPTR "] = %d\n", indiceBanca, saldoBanca[indiceBanca]);
        printf("numOperazioniBanca[%" PRIiPTR "] = %d\n", indiceBanca, numOperazioniPerBanca[indiceBanca]);
        usleep(TEMPOATTESA);
        printf("Thread DEPOSITI di banca %" PRIiPTR " rilascia mutex\n\n\n", indiceBanca);
        DBGpthread_mutex_unlock(&mutex, Plabel);
	}
	pthread_exit(NULL); 
}

void *Prelievi (void *arg) 
{ 
	char Plabel[128];
	intptr_t indiceBanca;

	indiceBanca=(intptr_t)arg;
	sprintf(Plabel,"Prelievi banca");

	/*  da completare  */

	while ( 1 ) {
        
		DBGpthread_mutex_lock(&mutex, Plabel);
        printf("Thread PRELIEVI di banca %" PRIiPTR " prende mutex\n", indiceBanca);
        saldoBanca[indiceBanca] -= 9;
        numOperazioniPerBanca[indiceBanca]++;
        printf("saldoBanca[%" PRIiPTR "] = %d\n", indiceBanca, saldoBanca[indiceBanca]);
        printf("numOperazioniBanca[%" PRIiPTR "] = %d\n", indiceBanca, numOperazioniPerBanca[indiceBanca]);
        usleep(TEMPOATTESA);
        printf("Thread PRELIEVI di banca %" PRIiPTR " rilascia mutex\n\n\n", indiceBanca);
        DBGpthread_mutex_unlock(&mutex, Plabel);
	}
	pthread_exit(NULL); 
}

void *BancaDiItalia (void *arg) 
{ 
	char Plabel[128];
    int i;
    int totaleDenaroBance;
    int totaleNumOperazioni;
	sprintf(Plabel,"BANCA DI ITALIA");

	/*  da completare  */

	while ( 1 ) {
        int totaleDenaroBance = 0;
        int totaleNumOperazioni = 0;
		DBGpthread_mutex_lock(&mutex, Plabel);
        for(i=0;i<NUMBANCHE;i++){
            totaleDenaroBance+=saldoBanca[i];
            totaleNumOperazioni+=numOperazioniPerBanca[i];           
        }
        printf("DENARO TOTALE: %d\nOPERAZ TOT: %d\n", totaleDenaroBance, totaleNumOperazioni);
        usleep(TEMPOATTESA*10);
        DBGpthread_mutex_unlock(&mutex, Plabel);
        sleep(SLEEPBANCADIITALIA);
	}
	pthread_exit(NULL); 
}


int main ( int argc, char* argv[] ) 
{ 
	pthread_t th; 
	int rc;
	uintptr_t i=0;
    uintptr_t j=0;

	rc = pthread_mutex_init(&mutex, NULL); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	DBGpthread_mutex_init(&mutex, NULL, "main");

	/* CREAZIONE PTHREAD */
    for(j=0;j<NUMBANCHE;j++){

        printf("Lancio DEPOSITI\n");

        for(i=0;i<NUMDEP;i++) {
            rc=pthread_create(&th,NULL,Depositi,(void*)j); 
                if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	    }

        printf("Lancio PRELIEVI\n");

        for(i=0;i<NUMPRELIEVI;i++) {
            rc=pthread_create(&th,NULL,Prelievi,(void*)j); 
                if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	    }

    }
	
    i=0;
    /*Creo thread unico BancaDiItalia*/
    rc=pthread_create(&th,NULL,BancaDiItalia,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");

	pthread_exit(NULL);
	return(0); 
} 
  

