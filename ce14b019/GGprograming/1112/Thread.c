#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h>


void *Thread_odo_send (void *arg);

int main(int argc, char **argv) { 
	int i ;
	pthread_t tid[3]; 
	pthread_attr_t attr;
	char * one[] = 
	{ "korea ploy technic university",
	  "computer engnieering",
	  "hong gil dong"};


	pthread_attr_init (&attr); 
	pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);

	sleep (1); 
	for( i = 0; i< 3; i++){
	if(pthread_create(&tid[i], &attr, Thread_odo_send, one[i])) { 
	fprintf(stderr, "Error: Thread_odo_send() \ Creation!\n"); 
	pthread_exit(0); }
	}

	if (pthread_join (tid[2], NULL) != 0) 
	fprintf (stderr, "ERROR: ptherad_join()");




	return 0;
}
void *Thread_odo_send (void *arg) { 
	while(1){
	char *tx = (char *) arg; 
	printf("%s\n",tx);
	}
	pthread_exit (0); 
}

