#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#define _POSIX_C_SOURCE 200112L
#define _BSD_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>

#define NUM_THREADS 1000

typedef struct{
	pthread_t th;
	int index;
}arg_struct;

void *do_thread(void *i)
{
	int error;
	void *ptr;
	pthread_t th;
	arg_struct* str;
	printf("thread index %d: thread_ID %d\n", (((arg_struct *)(i))->index), (int) pthread_self());
	usleep(1000);
	
	str = (arg_struct *)malloc(sizeof(arg_struct));
	if(str==NULL){
		printf("ERROREEE AIUTOOOOOOO\n");
		pthread_exit (NULL);	
	}
	str->th = pthread_self();
	str->index = ((((arg_struct *)(i))->index) + 1);

	pthread_create(&th, NULL, do_thread, str);
	error=pthread_join(((arg_struct *)(i))->th, &ptr);
		
	if(error!=0){
		printf("pthread_join() failed: error=%d\n", error ); 
		exit(-1);
	}
	
	pthread_exit (NULL);
}

int main(){
	arg_struct *i;
	pthread_t th;
	usleep(1000);

	i = (arg_struct *)malloc(sizeof(arg_struct));
	
	if(i==NULL){
		printf("ERROREEE AIUTOOOOOOO\n");
		exit(1);	
	}
	
	i->th = pthread_self();
	i->index = 1;
	
	pthread_create(&th, NULL, do_thread, &i);
	
	pthread_exit (NULL);
	return(0);
}

