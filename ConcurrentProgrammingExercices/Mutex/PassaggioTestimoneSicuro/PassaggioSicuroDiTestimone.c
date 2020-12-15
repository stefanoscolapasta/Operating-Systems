/* PassaggioDiTestimone.c */

#ifndef _THREAD_SAFE
  #define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
  #define _POSIX_C_SOURCE 200112L
#endif

#include "printerror.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include "DBGpthread.h"


#define NUMCORRIDORI 4

pthread_t tId;

pthread_mutex_t mutex;
pthread_cond_t cond_attesa_arrivo_precedente;
pthread_cond_t cond_passaggio_testimone;
int turno=0;

void *Corridore(void *arg){
	char Clabel[128]; 
	char Clabelsignal[128]; 
	int index=*((int*)arg);
	int mioturno;

 	free(arg);

	sprintf( Clabel, "C%d", index);
	sprintf( Clabelsignal, "C%d->C", index);

	DBGpthread_mutex_lock(&mutex, Clabel);
	turno++;
	mioturno=turno;
	if(mioturno!=1) {
		/*	attendo che il corridore precedente mi appoggi il testimone */
		DBGpthread_cond_wait(&cond_attesa_arrivo_precedente,&mutex, Clabel);

		/*	mi hanno appoggiato il testimone in mano, lo afferro,
			poi urlo per avvisare che possono mollarlo 
		*/
		DBGpthread_cond_signal(&cond_passaggio_testimone, Clabelsignal);

		/* attendo l'urlo di conferma di avere mollato il testimone */
		DBGpthread_cond_wait(&cond_passaggio_testimone,&mutex, Clabel);
	}

	printf("C%d parte\n",index);
	DBGpthread_mutex_unlock(&mutex, Clabel);

	sleep(1);
	printf("C%d ha completato il giro\n",index);
		
	DBGpthread_mutex_lock(&mutex, Clabel);
	if(mioturno<NUMCORRIDORI) {
		/*	appoggio il testimone in mano al successivo ma non lo mollo */
		DBGpthread_cond_signal(&cond_attesa_arrivo_precedente, Clabelsignal);

		/*	attendo l'urlo del successivo prima di mollare il testimone */
		DBGpthread_cond_wait(&cond_passaggio_testimone,&mutex, Clabel);

		/*	il successivo mi ha urlato di mollare il testimone,
			mollo il testimone e
			urlo al successivo che ho mollato e puo' partire 
		*/
		DBGpthread_cond_signal(&cond_passaggio_testimone, Clabelsignal);

		printf("C%d ha lasciato il testimone e termina\n",index);
	}
	else { 
		printf("L'ultimo C%d ha completato il giro\n",index);
	}
	DBGpthread_mutex_unlock(&mutex, Clabel);
	pthread_exit(NULL); 
}

int main(){
	int rc,i, *p;
	
	rc = pthread_cond_init(&cond_attesa_arrivo_precedente, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init(&cond_passaggio_testimone, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_mutex_init(&mutex, NULL); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");
	
	
	DBGpthread_mutex_lock(&mutex, "main");
	/*creo i thread */
	for(i=0;i<NUMCORRIDORI;i++) {

                /* alloco la struttura in cui passare i parametri */
                p=malloc(sizeof(int));
                if(p==NULL) {
                        perror("malloc failed: ");
                        exit (1);
                }
                *p=i;

		rc=pthread_create( &tId, NULL, Corridore, (void*)p ); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	/* per semplificare l'inizio, il main aspetta 3 secondi 
	   che tutti i thread siano partiti e arrivati alla lock iniziale,
	   poi rilascia la mutua esclusione
	*/
	sleep(3);
	DBGpthread_mutex_unlock(&mutex, "main");

	pthread_exit(NULL); 
	return 0;
}
