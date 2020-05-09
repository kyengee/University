#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30


void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock, file, str_len=0;
	char name[BUF_SIZE];
	struct sockaddr_in serv_adr;
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error!");
	else
		puts("Connected...........");

	fputs("file name : \n", stdout);
	scanf("%s", name);
	printf("finding %s...\n", name);


	if ((file = open(name, O_RDONLY))==-1) {
		printf("File not exist");
		write(sock,"end", strlen("end"));
		close(sock);
		return 0;
	}
	else {
		fputs("make file name : \n", stdout);
		scanf("%s", name);
		printf("make %s...", name);
		write(sock, name, strlen(name));
		read(sock, name, BUF_SIZE);
		while ((str_len = read(file, name, strlen(name)))!=0) {		
			printf("%s",name);
			write(sock,name, str_len);
		}
		close(sock);

	}


	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

