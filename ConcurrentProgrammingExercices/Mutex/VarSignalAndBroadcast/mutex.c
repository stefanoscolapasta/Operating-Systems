/* mutex.c */

/* simboli già messi nella riga di comando del compilatore 
#define _THREAD_SAFE
#define _REENTRANT
#define _POSIX_C_SOURCE 200112L
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include "printerror.h"
#define NUMTHRDS 10

pthread_t callThd[NUMTHRDS];
pthread_mutex_t mutexdata;   
/* this variable can be initialized statically with default attributes, using
   pthread_mutex_t mutexdata = PTHREAD_MUTEX_INITIALIZER;  
   same as pthread_mutex_init(...,NULL)
   but with NO ERROR CHECKING 
*/

int data;

void *decrementa(void *arg)
{
	int rc;
	rc = pthread_mutex_lock (&mutexdata);  /* provare a commentare */ 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_lock failed"); /* no EINTR */
	if(data>0) {
		sleep(1); /* provare a decommentare */
		data--;
	}
	rc = pthread_mutex_unlock (&mutexdata); /* provare a commentare */
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_unlock failed"); /* no EINTR */
	pthread_exit((void*) 0);
}

int main (int argc, char *argv[])
{
	intptr_t i;
	int rc; void *ptr; 

	data=NUMTHRDS/2;
	rc = pthread_mutex_init (&mutexdata, NULL);
	if( rc != 0 ) PrintERROR_andExit(errno,"pthread_mutex_init failed"); /* no EINTR */
	for(i=0;i < NUMTHRDS;i++) 	{
		/* per default i thread consentono il join, */
		/* NB: COME FARE CAST PER ASSEGNARE L'INTERO i AL PUNTATORE void*.
		- il cast (void*)i da' warning perche' l'intero i ha size diversa
		- il doppio cast (void*)((int64_t)i) funziona solo su sist a 64bit
		  dove la dimensione del puntatore e' di 64 bit, 
		  ma su sist a 32 bit da' warning perche' dice che nel passaggio
		  da int64_t a void* ho due dimensioni diverse e perdo dei bytes.
		- il doppio cast (void*)((int32_t)i) funziona solo su sist a 32bit
		  dove la dimensione del puntatore e' di 32 bit, 
		  ma su sist a 64 bit da' warning perche' dice che nel passaggio
		  da int32_t a void* ho due dimensioni diverse.
		- il modo corretto e' fare un cast utilizzando un particolare
		  tipo di dato intero, definito in sydint.h e denominato
		  intptr_t (oppure uintptr_t) che e' un intero con (o senza) segno
		  che ha le stesse dimensioni di un puntatore.
		  Ovviamente la dimensione di questo tipo di dato dipende dal fatto
		  che il sistema e' a 32 o 64 bit.
		*/
		rc = pthread_create ( &callThd[i], NULL, decrementa, (void *)i );
		if( rc != 0 ) PrintERROR_andExit(rc,"pthread_create failed"); /* no EINTR */
	}

	for(i=0;i < NUMTHRDS;i++) { /* aspetto la fine dei thread */
		rc = pthread_join ( callThd[i], &ptr);
		if( rc != 0 ) PrintERROR_andExit(rc,"pthread_join failed"); /* no EINTR */
	}
	printf ("data = %d \n", data);
	rc = pthread_mutex_destroy (&mutexdata);
	if( rc != 0 ) PrintERROR_andExit(rc,"pthread_mutex_destroy failed");  /* no EINTR */
	return(0);
}

