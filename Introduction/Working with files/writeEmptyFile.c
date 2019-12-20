#include <stdio.h>
void main() {
	FILE *fptr;
	fptr = fopen("test.md", "w+");
	if (fptr == NULL) {
		printf("Unable to open file");
	}
	else {
		fputs("Hello world test file", fptr);
		fclose(fptr);
	}	
}