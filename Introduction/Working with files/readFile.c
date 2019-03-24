#include <stdio.h>

void main() {
	FILE *stream;
	char msg[81];
	stream = fopen("open.c","r");
	fgets(msg, 81, stream);
	printf("%s\n",msg );
	fclose(stream); // without fclose() still run fine
}
/*
Result: Printout the content inside file "open.c"
*/