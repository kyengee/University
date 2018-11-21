#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int status;
	pid_t pid=fork();
	
	if(pid==0)     // if Child Process
	{
		sleep(3);
		return 3;
	}
	else{
		printf("child PID : %d \n",pid);
		printf("%d\n",waitpid(-1,&status,WNOHANG));
		printf("%d\n",wait(&status));
		printf("%d\n",waitpid(-1,&status,WNOHANG));
	}

	return 0;
}

