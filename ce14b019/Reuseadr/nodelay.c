#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/tcp.h>

#define TRUE 1
#define FALSE 0
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	char message[30];
	int option, str_len;
	socklen_t optlen, clnt_adr_sz;
	struct sockaddr_in serv_adr, clnt_adr;
	
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock==-1)
		error_handling("socket() error");
	
	optlen=sizeof(option);
	option=TRUE;	
	setsockopt(serv_sock, SOL_SOCKET, TCP_NODELAY, &option, optlen);
	printf("prev %d",option);
	
	option=FALSE;	
	setsockopt(serv_sock, SOL_SOCKET, TCP_NODELAY, &option, optlen);
	printf("after %d",option);
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
