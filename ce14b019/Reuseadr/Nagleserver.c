#include <netinet/tcp.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int file, str_len,i;
	char name[BUF_SIZE];
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	int option;
	socklen_t optlen;
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");
	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");
	clnt_adr_sz = sizeof(clnt_adr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
	if (clnt_sock == -1)
		error_handling("accept() error");
	puts("client detected");



	optlen = sizeof(option);
	option = 1;
	getsockopt(serv_sock, SOL_SOCKET, TCP_NODELAY, (void*)&option, optlen);
	printf("%d", option);
	



	close(file);
	close(clnt_sock);
	close(serv_sock);
	return 0;
}



void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}



