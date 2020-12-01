/* cancel.c  
Esempio di creazione di pthread
e di terminazione di uno di questi su richiesta
*/

/* igia' messi nella riga di comando del compilatore 
#define _THREAD_SAFE
#define _REENTRANT
#define _POSIX_C_SOURCE 200112L
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

int Glob=10;
void *do_thread(void *p_index)
{
	int ris, i=0;

	/*
	 la riga qui sotto servirebbe ad impedire al pthread di terminare
	 anche se qualcuno invoca la pthread_cancel su di lui
	 pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
	*/
	sleep(1);
	Glob+=3;
	printf("thread index %d: Glob=%d thread_ID %d\n", *((int*)p_index), Glob, (int)pthread_self() );


        /* uso in qualche modo l'indice che mi e' stato passato */
        ris =  *((int*)p_index);
        ris = - ris ; /* lo cambio di segno, per gioco */

	while(i<10)
	{
		/*sleep(1);*/
		printf("thread index %d: thread_ID %d  ITERAZIONE %d\n", *((int*)p_index), (int)pthread_self(), i );
		i++;

	}


	/* dealloco la struttura in cui mi sono stati passati i parametri */
	free(p_index);

	pthread_exit ( NULL );  /* valore restituito dal thread */
}

int main()
{
	pthread_t vthreads[NUM_THREADS];
	int rc, t, *p;
	pthread_attr_t attr;

	printf("il main e' il thread con ID %d\n", (int) pthread_self() );

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	for(t=0;t < NUM_THREADS;t++){

		/* alloco la struttura in cui passare i parametri */
		p=malloc(sizeof(int));
		if(p==NULL) {
			perror("malloc failed: ");
			pthread_exit (NULL);
		}
		*p=t;


		/* printf("Creating thread DETACHED %d\n", t); */
		rc = pthread_create (&vthreads[t], &attr, do_thread, p );
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n",rc);
			exit(-1);
		}
		else{
			printf("Created thread DETACHED ID %d\n", (int)(vthreads[t]) );
		}
			
	}
	pthread_attr_destroy(&attr);
	/* uccido i primi 4 pthread */
	for(t=0;t<NUM_THREADS-1;t++){
		pthread_cancel(vthreads[t]);
	}
	
	/* se chiamo la pthread_exit
	   i thread creati continuano l'esecuzione anche dopo la fine del main
	*/
	pthread_exit (NULL);

	/* se invece chiamo la exit normale o la return
	   i thread creati vengono interrotti con la fine del main
	*/
	exit(0);

}
