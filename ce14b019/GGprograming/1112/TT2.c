#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct net_t_tag {
  char *univ;   
  char *dep ;
  char *name;
  char str[100];
} net_t;
void *Thread_odo_send (void *arg);
int main(int argc, char **argv)
{
 int i;
 pthread_t tid;
 pthread_attr_t attr;
 net_t tx;
 tx.univ = "aaa";
 tx.dep = "hhh";
 tx.name = "fff";
 pthread_attr_init(&attr);
 pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
 sleep(1);
 if(pthread_create(&tid, &attr, Thread_odo_send, &tx)) {
 fprintf(stderr, "Error: Thread_odo_send() \
 Creation!\n");
 pthread_exit(0);
}

if (pthread_join (tid, NULL) != 0)
fprintf (stderr, "ERROR: ptherad_join()");
return 0;
}
void *Thread_odo_send (void *arg)
{
net_t *tx = (net_t *)arg;
int i;
 fprintf(stderr,"%s \n",tx->univ);
 fprintf(stderr,"%s \n",tx->dep);
 fprintf(stderr,"%s \n",tx->name);
pthread_exit (0);
}
