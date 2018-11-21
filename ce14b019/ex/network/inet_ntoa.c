#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	struct sockaddr_in addr1, addr2;
	char *str_ptr;
	char str_arr[20];
	
	addr1.sin_addr.s_addr=htol(0x1020304);
	addr2.sin_addr.s_addr=htol(0x1919191);

