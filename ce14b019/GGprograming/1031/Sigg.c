#include <signal.h>

void catchint(int signo);
void catchalarm(int signo);

int main(){

  static struct sigaction act;
  static struct sigaction act2;

  act.sa_handler = catchint;
  act2.sa_handler = catchalarm;

  sigfillset(&(act.sa_mask));

  sigaction(SIGINT, &act, NULL);
  sigaction(SIGALRM, &act2, NULL);

  printf("Sleep call #1\n");
  sleep(1);
  printf("Sleep call #2\n");
  sleep(1);
  printf("Sleep call #3\n");
  sleep(1);
  printf("Sleep call #4\n");
  sleep(1);
  printf("Starting ALARM 5sec\n");
  alarm(5);

  sleep(6);

  printf("Exiting\n");
  exit(0);
}

void catchint(int signo){

  printf("\nCATCHINT: signo =%d\n", signo);

  printf("CATCHINT: returning\n\n");
}

void catchalarm(int signo){

  printf("\nCATCHALRAM: signo =%d\n", signo);

  printf("CATCHALARM: returning\n\n");
} 
