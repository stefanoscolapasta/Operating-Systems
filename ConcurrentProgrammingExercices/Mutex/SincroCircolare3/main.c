#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int turno = 0;
int var_globale = 33;
pthread_mutex_t mutex;
pthread_cond_t cond;

void *thread_function(void* arg){
	intptr_t mioindice = ((intptr_t)arg);
	while(1){
		pthread_mutex_lock(&mutex);
		while(turno != mioindice){
			pthread_cond_wait(&cond,&mutex);
			if(turno != mioindice){
				pthread_cond_signal(&cond);
			}
		}
		
		var_globale = var_globale + 3;
		turno = (turno+1)%3;
		printf("Turno di: %d\n", turno);
		pthread_cond_signal(&cond);
		
		pthread_mutex_unlock(&mutex);
	}
}

int main(){
	int i;
	intptr_t t[] = {0,1,2};
	pthread_t tid;
	
	for(i=0;i<3;i++){
		printf("INDICE: %" PRIiPTR "\n", t[i]);
		pthread_create(&tid, NULL, thread_function, (void *)t[i]);	
	}
	
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
	return(0);
}
