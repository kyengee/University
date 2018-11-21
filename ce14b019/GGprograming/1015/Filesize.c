#include <stdio.h>

long filesize(FILE *stream)
{
	long curpos, length;

	curpos = ftell(stream);
	fseek(stream,0L,SEEK_END);
	length = ftell(stream);
	fseek(stream, curpos, SEEK_SET);
	return length;
}

int main(int argc,char** argv){

	FILE *stream;
	if(argc < 2){
	printf("No Input!\n");
	return 0;}
	stream = fopen(argv[1],"r");

	printf("size of the <%s> file : %ld Bytes \n",
	argv[1],filesize(stream));
	return 0;
}

