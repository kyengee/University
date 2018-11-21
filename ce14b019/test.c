#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char *s = "sfsfsf";
	printf("1");
	printf("var s has %s at %p\n", s, s);
	s = (char *)malloc(sizeof(char) * 16);
	*s = 'C';
	printf("2");
	printf("var s has %s at %p\n", s, s);
	strcpy(s, "kpu");
	printf("3");
	printf("var s has %s at %p\n", s, s);
	free(s)ddddddddddddddddd
