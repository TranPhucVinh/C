// Write content to files

#include <stdio.h>
void main() {

	FILE *file;
	file = fopen("text.md", "w+"); // this can be .md, .txt, ....
	if (file == NULL) {
		printf("Unable to open file");
	}
	else {
		fputs("Hello world", file);
		fclose(file); // without this is ok
	}
	
}