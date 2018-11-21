#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h>

static int addnum = 0;
pthread_mutex_t mutexsum;
void *Thread_add (void *arg);

int main(int argc, char **argv) { 
	int i=0;
	pthread_t tid[3]; 
	pthread_attr_t attr;

	pthread_attr_init (&attr); 
	pthread_mutex_init(&mutexsum,NULL);
	pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);

	sleep (1); 
	for(i = 0; i< 3;i++){
	if(pthread_create(&tid[i], &attr, Thread_add,NULL )) { 
	fprintf(stderr, "Error: Thread_add()  Creation!\n"); 
	}
	}


	if (pthread_join (tid[2], NULL) != 0) 
	fprintf (stderr, "ERROR: ptherad_join()");
	
	pthread_mutex_destroy(&mutexsum);



	return 0;
}
void *Thread_add (void *arg) { 
	while(1){
	pthread_mutex_lock(&mutexsum);	
	addnum++;
	fprintf(stderr,"Thread#%d: value=%d\n",pthread_self(),addnum);
	pthread_mutex_unlock(&mutexsum);
	sleep(1);
	}
	pthread_exit (0); 
}


