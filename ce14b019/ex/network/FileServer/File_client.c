#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock, fd;
	char message[BUFF_SIZE];
	int str_len;
	struct sockaddr_in serv_adr;

	if(argc!=3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_STREAM, 0);   
	if(sock==-1)
		error_handling("socket() error");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));
	
	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("connect() error!");
	else
		puts("Connected...........");
	
	while(1) 
	{
		str_len = read(sock,message,1);
		switch(atoi(message)){
			case 0:
				str_len = read(sock,message,BUFF_SIZE-1);
				message[str_len] = 0;
				printf("%s",message);
				fgets(message, BUFF_SIZE, stdin);	
				write(sock,message,strlen(message));
			case 1:
				puts("make file name: /n");	
				scanf("%s",message);
				if((fd = open(message,O_RDWR|O_CREAT,0644)) == -1)error_handling("File create error");
				while(1){
					str_len = read(sock,message,10);
					message[str_len] = 0;	
					if(str_len<=0)break;
					printf("%s",message);
					write(fd,message,str_len);
					}
			default:
				break;
		}
				
				
				





	}
	clise(fd);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
