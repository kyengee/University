#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *t_function(void *data)
{
    char *p = NULL;
   p = malloc(512);
   p = data;
   printf("%s\n", p);
}
 
int main()
{
    pthread_t p_thread[2];
    int thr_id;
    int status;
    char p1[] = "thread_1";  
    char p2[] = "thread_2";   
    char pM[] = "thread_m";  
 
 
    sleep(1);  
 
    if (pthread_create(&p_thread[0], NULL, t_function, (void *)p1))
    {
        perror("thread create error : ");
        pthread_exit(0);
    }
 
   sleep(1);  
 
    if (thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)p2))
    {
        perror("thread create error : ");
        pthread_exit(0);
    }
 
    pthread_join(p_thread[0], (void **)&status);
    pthread_join(p_thread[1], (void **)&status);
 
    return 0;
}
