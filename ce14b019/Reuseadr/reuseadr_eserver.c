#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TRUE 1
#define FALSE 0
void error_handling(char *message){
	puts("%s error occered",message);
	exit(1);
}

int main(int argc, char *argv[]){
	int serv_sock,clnt_sock;
	char message[30];
	int option,str_len;
	socklen_t optlen,clnt_adr_sz;
	struct sockaddr_in serv_adr, clnt_adr;
	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
}

	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	if(serv_sock==-1)
		error_handling("sock() error");

	optlen=sizeof(option);
	potion=TRUE;
	setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,(void*)&option,optlen);

	memset(&serv_adr,0,sixeof(serv_adr));
	serv_adr.sinfamliy = AF_INET;
	serv_adr.sin_sddr.s_addr=hyonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	
	if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr)))
		error_handling("bind() error");
	if(listen(serv_sock,5)==-1)
		error_handling("

	

