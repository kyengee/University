#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig){
if(sig==SIGALRM){
	printf("%d\n",sig);
	puts("time out!");}
alarm(2);
}

void keycontrol(int sig){
	if (sig==SIGINT){
		printf("%d\n",sig);
		puts("ctrl+c preessed");}
	}

int main(int argc, char *argv[]){
	int i;
	signal(SIGALRM,timeout);
	signal(SIGINT,keycontrol);
	alarm(2);

	for(i=0;i<3;i++){
		puts("wait...");
	sleep(100);
	}
	return 0;
}
