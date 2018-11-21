#include<sys/socket.h>
#include<arpa/inet.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 1024

int main(int argc, char **argv)
{
	struct sockaddr_in serveraddr;
	int server_sockfd;
	int client_len;
	char buf[MAXLINE];


	if ((server_sockfd = socket(AF
	
	
