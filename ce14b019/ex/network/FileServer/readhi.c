#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	char message[]="hi.txt";
	char *ff = "hi.txt";
	int cnt = open("hi.txt",O_RDONLY);
	printf("%d\n",cnt);
	cnt = open("./hi.txt",O_RDONLY);
	printf("%d\n",cnt);
	cnt = open(message,O_RDONLY);
	printf("%d\n",cnt);	
	cnt = open(ff,O_RDONLY);
	printf("%d\n",cnt);
return 0;
}
