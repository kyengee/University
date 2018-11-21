#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h>

static int signal = 0;
void *Thread_odo_send (void *arg);
void *Thread_odo_receive (void *arg);

int main(int argc, char **argv) { 
	pthread_t tid[2]; 
	pthread_attr_t attr;
	char * one = malloc(sizeof(char)*100);


	pthread_attr_init (&attr); 
	pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);

	sleep (1); 
	if(pthread_create(&tid[0], &attr, Thread_odo_send, &one)) { 
	fprintf(stderr, "Error: Thread_odo_send()  Creation!\n"); 
	}

	if(pthread_create(&tid[1], &attr, Thread_odo_receive, &one)) {
	fprintf(stderr, "Error: Thread_odo_send()  Creation!\n");
	}

	if (pthread_join (tid[1], NULL) != 0) 
	fprintf (stderr, "ERROR: ptherad_join()");




	return 0;
}
void *Thread_odo_send (void *arg) { 
	char *tx = (char *) arg; 
	strcpy(tx,"ggg");
	fprintf(stdout,"%s\n",tx);
	signal = 1;
	pthread_exit (0); 
}

void *Thread_odo_receive( void *arg){
	char *tx = (char *) arg;
	while(signal != 1){
	sleep(5);
	}
	fprintf(stdout,"receive %s\n",tx);
	pthread_exit (0);
}

