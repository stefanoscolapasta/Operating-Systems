#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#define _POSIX_C_SOURCE 200112L
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define NUM_THREADS 4

typedef struct{
	int N;
	char s[100];
	int index;
}S;

void *func(void *arg){
	S *tSt1, *tSt2;
	int t, res;

	tSt1 = (S*)arg;
	printf("Inizio THREAD %d di INDICE %d \n", tSt1->N, tSt1->index);
	fflush(stdout);
	sleep(1);

	if(tSt1->N > 1){
		pthread_t vTh[NUM_THREADS];
		for(t = 0; t < tSt1->N; t++){
			tSt2=(S*)malloc(sizeof(S));
			if(tSt2==NULL){
				perror("malloc failed");
				exit(1);
			}
			tSt2->N=tSt1->N-1;
			tSt2->index=t;
			strcpy(tSt2->s,"ciao");
			res = pthread_create(&vTh[t], NULL, func, (void*)tSt2);
			if (res) {
				printf("ERROR; return code from pthread_create() is %d\n",res);
				exit(1);
			}
		}
		for(t=0; t < tSt1->N; t++){
			res=pthread_join(vTh[t], (void**)&tSt2);
			if (res) {
				printf("ERROR; return code from pthread_join() is %d\n",res);
				exit(1);
			}
			printf("received \"%s\"\n", tSt2->s);
			fflush(stdout);
			free(tSt2);
		}
		
	}
	sprintf(tSt1->s, "%d %d",tSt1->N,tSt1->index); 
	pthread_exit((void*)tSt1);
}

int main(){
	S *st;
	pthread_t vTh[NUM_THREADS];
	int res, t;
	
	for(t=0; t<NUM_THREADS; t++){
		st = (S*)malloc(sizeof(S));
		if(st==NULL){
			perror("malloc failed");
			exit(1);
		}
		st->N = NUM_THREADS - 1;
		st->index = t;
		strcpy(st->s,"Ciao");
		printf("Creating thread %d\n", t);
		fflush(stdout);
		res = pthread_create(&vTh[t], NULL, func, (void*)st);
		if (res) {
			printf("ERROR; return code from pthread_create() is %d\n",res);
			exit(1);
		}
	}
	
	for(t=0; t< NUM_THREADS; t++){
		res = pthread_join(vTh[t], (void**)&st ); 
		if (res) {
			printf("ERROR; return code from pthread_join() is %d\n",res);
			exit(1);
		}
		printf("main received \"%s':\n", st->s);
		fflush(stdout);
		free(st);
	}
	
	printf("Finished\n");
	pthread_exit(NULL);
	return(0);
}
