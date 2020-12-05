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

/* this variable can be initialized statically with default attributes, using
   pthread_mutex_t mutexdata = PTHREAD_MUTEX_INITIALIZER;  
   same as pthread_mutex_init(...,NULL)
   but with NO ERROR CHECKING 
*/

#define NUMSPADE 10
#define NUMFACHIRI 2

pthread_mutex_t  mutex[NUMSPADE];
pthread_cond_t cond;
void *trafiggi0(void *arg)
{
	int i, rc;
	while(1){
			
			for(i = 0; i < NUMSPADE; i++){
				pthread_cond_wait(&cond, &(mutex[i]));
				rc = pthread_mutex_lock(&(mutex[i]));
				if(rc!=0) {perror("lock failed\n");exit(1);}
			}
			
			for(i = 0; i < NUMSPADE; i++){
				printf("AAAAA FACHIRO %d TRAFITTO CON LA SPADA %d\n",*((int *)arg), i);
			}
			pthread_cond_signal(&cond);				
			for(i = 0; i < NUMSPADE; i++){
				rc = pthread_mutex_unlock(&(mutex[i]));
				if(rc!=0) {perror("unlock failed\n");exit(1);}
			}	
		}
	pthread_exit(NULL); 
}

void *trafiggi1(void *arg)
{
	int i, rc;
	while(1){
			
			for(i = 0; i < NUMSPADE; i++){
				pthread_cond_wait(&cond, &(mutex[i]));
				rc = pthread_mutex_lock(&(mutex[i]));
				if(rc!=0) {perror("lock failed\n");exit(1);}
			}
			
			for(i = NUMSPADE-1; i == 0; i++){
				printf("AAAAA FACHIRO %d TRAFITTO CON LA SPADA %d\n",*((int *)arg), i);
			}
			pthread_cond_signal(&cond);	
			for(i = 0; i < NUMSPADE; i++){
				rc = pthread_mutex_unlock(&(mutex[i]));
				if(rc!=0) {perror("unlock failed\n");exit(1);}
			}	
		}
	pthread_exit(NULL); 
}
	

int main()
{
	pthread_t th; 
	int * d;
	int i, rc;
	
	for(i=0;i<NUMSPADE;i++) {
		rc = pthread_mutex_init(&mutex[i], NULL);
		if (rc){perror("pthread_mutex_init failed");exit(1);}
	}
	
	for(i = 0; i < NUMFACHIRI; i++) {
		d = (int *)malloc(sizeof(int));
		*d = i;
		printf("FACHIRO %d  LANCIATO\n\n", *d);
		if(*d==0){
			rc=pthread_create( &th, NULL,trafiggi0,(void*)d); 
			printf("LANCIO 1 \n");
		} else {
			rc=pthread_create( &th, NULL,trafiggi1,(void*)d); 
			printf("LANCIO 2 \n");
		}
		
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	pthread_exit(NULL); 

	return(0); 
}

