#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
	char *addr="127.232.124.79";
	struct sockaddr_in addr_inet;
	int i = 0;

	if(!inet_aton(addr, &addr_inet.sin_addr))
		error_handling("Conversion error");
	else
		printf("Network ordered integer addr: %#x \n",
			addr_inet.sin_addr.s_addr);
	addr_inet.sin_addr.s_addr = inet_ntoa(INADDR_ANY);
	printf("%#x\n", addr_inet.sin_addr.s_addr);
	printf("%s\n", addr_inet.sin_addr.s_addr);
	printf("%#x\n",INADDR_ANY);
	printf("%s\n",INADDR_ANY);
	printf("%d\n",INADDR_ANY);


	return 0;
}

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n', stderr);
	exit(1);
}
