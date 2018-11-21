#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
	FILE *fp;
	int sock;
	char message[BUFF_SIZE];
	char File_data[BUFF_SIZE];
	int str_len;
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
		puts("find file name:");
	fgets(message, BUFF_SIZE, stdin);
	write(sock, message, strlen(message));

	str_len = read(sock, File_data, BUFF_SIZE);

	puts("save file name:");
	fgets(message, BUFF_SIZE, stdin);
	if ((fp = fopen(message, "a")) == NULL)
		error_handling("file.write() error");
	fwrite(File_data, 1, BUFF_SIZE, fp);
	

	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
