#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100
void error_handling(char *message);
void read_childproc(int sig);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock, file;
	struct sockaddr_in serv_adr, clnt_adr;
	int fds[2];
	
	pid_t pid;
	struct sigaction act;
	socklen_t adr_sz;
	int str_len, state;
	char buf[BUF_SIZE], fname[BUF_SIZE];
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	act.sa_handler=read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	state=sigaction(SIGCHLD, &act, 0);

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	fputs("Input FileName: ", stdout);
	fgets(fname, BUF_SIZE, stdin);
	fname[strlen(fname)-1]='\0';
	pipe(fds);
	pid=fork();
	if(pid==0)
	{
		char fbuf[BUF_SIZE];
		read(fds[0], fbuf, BUF_SIZE);
		file=open(fbuf, O_WRONLY|O_CREAT, 0644);
		int len, i;

		for(i=0; i<10; i++) 
		{
			char msgbuf[BUF_SIZE] = {};
			len=read(fds[0], msgbuf, BUF_SIZE);
			write(file, msgbuf, strlen(msgbuf));
			write(file, "\n", sizeof(int));
		}
		return 0;
	}

	while(1)
	{
		adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
		if(clnt_sock==-1)
			continue;
		else 
			puts("new client connected...");
		
		pid=fork();
		if(pid==0)
		{
			close(serv_sock);
			write(fds[1], fname, strlen(fname));

			while((str_len=read(clnt_sock, buf, BUF_SIZE))!=0)
			{
				buf[str_len]=0;
				buf[str_len-1]=0;
				printf("Read Message : %s\n", buf);
				write(fds[1], buf, strlen(buf));
				if(!strcmp(buf, "q")||!strcmp(buf, "Q")) {
					char *buff="End of Message\n";
					write(clnt_sock, buff, BUF_SIZE);
				}
				else {
					write(clnt_sock, buf, str_len);
				}
			}
			
			close(clnt_sock);
			puts("client disconnected...");
			return 0;
		}
		else
			close(clnt_sock);
	}
	close(serv_sock);
	return 0;
}

void read_childproc(int sig)
{
	pid_t pid;
	int status;
	pid=waitpid(-1, &status, WNOHANG);
	printf("removed proc id: %d \n", pid);
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
