#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUFF_SIZE 1024


void error_handling(char *message) {

	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}



int main(int argc, char *argv[]) {

	FILE *fp;
	int serv_sock, clnt_sock, File_sock;
	char message[BUFF_SIZE];
	char *File_name;
	int str_len;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;

	if (argc != 2) {

		printf("Usage :%s <PORT>\n", argv[0]);
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
		error_handling("bind() error");


	clnt_adr_sz = sizeof(clnt_adr);

	puts("waiting Client..........\n");

	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
	puts("Client connected successfuly\n");
	if (clnt_sock == -1)
		error_handling("accept() error");
	str_len = read(clnt_sock, message, BUFF_SIZE);
	message[str_len] = 0;
	File_name = (char*)malloc(str_len);
	strcpy(File_name, message);
	if((fp = fopen(File_name, "r")) == NULL)
		error_handling("fileread() error");
	while (0 < (str_len = fread(message, 1, BUFF_SIZE, fp)))
	{
		write(clnt_sock, message, str_len);
	}
	

			close(clnt_sock);
			close(serv_sock);

			return 0;
		}
	


