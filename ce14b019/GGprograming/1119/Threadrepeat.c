#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h>

int count = 0;
pthread_mutex_t cons_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cons_cond = PTHREAD_COND_INITIALIZER;

void *Thread_print (void *arg);


int main(int argc, char **argv) { 
	int i=0;
	pthread_t tid[3]; 
	pthread_attr_t attr;


	pthread_attr_init (&attr); 
	pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);

	sleep (1); 
	for(i = 1; i< 4;i++){
	if(pthread_create(&tid[i], &attr, Thread_print,&i ))  
	fprintf(stderr, "Error: Thread_add()  Creation!\n"); 
	}
	pthread_mutex_lock (&cons_lock); 
	count = 1;
	pthread_mutex_unlock (&cons_lock);
	pthread_cond_signal (&cons_cond);




	if (pthread_join (tid[2], NULL) != 0) 
	fprintf (stderr, "ERROR: ptherad_join()");
	
	pthread_mutex_destroy(&cons_lock);



	return 0;
}

void *Thread_print (void *arg) { 
	int val = *((int *)arg);
	while(1){
		pthread_cond_wait(&cons_cond, &cons_lock);
		pthread_mutex_lock (&cons_lock);
		if(val == count)
	switch(val){
		case 1:
			fprintf(stdout,"Korea politechnic university");
			count = 2;
			break;
		case 2:
			fprintf(stdout,"computer Science");
			count = 3;
			break;
		case 3:
			fprintf(stdout,"hong gil dong");
			count = 1;
			break;
	}
	pthread_mutex_unlock (&cons_lock);
	}
	pthread_exit (0); 
}


