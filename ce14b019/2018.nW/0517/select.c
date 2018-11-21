#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 100

int main(int argc,char *argv[])
{
	fd_set reads,temps;
	int result, str_len;
	char buf[BUF_SIZE];
	struct timeval timeout;

	FD_ZERO(&reads);
	FD_SET(0,&reads);
	
	timeout.tv_sec=NULL;
	timeout.tv_usec=NULL;
	printf("first tv_sec = %d\n",timeout.tv_sec);
	printf("first tv_usec = %d\n",timeout.tv_usec);

	while(1)
	{
		temps=reads;
		result=select(1,&temps,0,0,&timeout);
		if(result==-1)
		{
			puts("select() error!");
			break;
		}
		else if(result==0)
		{
			puts("Time-out!");
		}
		else
		{
			if(FD_ISSET(0,&temps))
			{
				str_len=read(0,buf,BUF_SIZE);
				buf[str_len]=0;
				printf("mesage from console:%s",buf);
			}
		}
		printf("after select tv_sec = %d\n",timeout.tv_sec);
		printf("after select tv_usec = %d\n",timeout.tv_usec);
	}
	return 0;
}

	
