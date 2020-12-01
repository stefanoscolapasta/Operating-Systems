#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#define _POSIX_C_SOURCE 200112L
#define _DEFAULT_SOURCE
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
	void *ptr;
	pthread_t th;
	arg_struct* str;
	arg_struct* p = (arg_struct*)i;
	int res;
	
	printf("thread index %d: thread_ID %d\n", p->index, (int) pthread_self());
	usleep(1);
	
	str = (arg_struct *)malloc(sizeof(arg_struct));
	if(str==NULL){
		perror("malloc failed");
		exit(1);	
	}
	
	str->th = pthread_self();
	str->index = (p)->index + 1;

	res = pthread_create(&th, NULL, do_thread, (void *)str);
	if(res){
		printf("pthread_create() failed: error %i\n", res);
		exit(1);
		}
		
	res = pthread_join(p->th, &ptr);
	if(res != 0){
		printf("pthread_join() failed: error %i\n",res);
		exit(1);
	}
	
	free(i);
	pthread_exit(NULL);
}

int main(){
	arg_struct *i;
	pthread_t th;
	usleep(1000);

	i = (arg_struct *)malloc(sizeof(arg_struct));
	
	if(i==NULL){
		perror("malloc failed");
		exit(1);	
	}
	
	i->th = pthread_self();
	i->index = 1;
	
	pthread_create(&th, NULL, do_thread, (void *)i);
	printf("FINEEEEEE\n");
	pthread_exit (NULL);
	
	return(0);
}

