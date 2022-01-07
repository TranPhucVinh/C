#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define ELEMENT_NUMBERS 1
#define SIZE_OF_LINE 30

int total_line;
int get_file_total_line(char *file_name);

int main(int argc, char *argv[]) {
	total_line = get_file_total_line("test.c");
	//Can only define the string array here as total line must be const value
	char string_array[total_line][SIZE_OF_LINE];

	FILE *fptr = fopen("test.c", "r");
	int index = 0;
	while (index < total_line){
      if (fgets(string_array[index], SIZE_OF_LINE, fptr) == NULL) break;
      else {
		//Remove the \n character
		if(string_array[index][SIZE_OF_LINE-2] == '\n') string_array[index][SIZE_OF_LINE-2] ='\0';
		index++;
      }   
   }
   for (int i=0; i < total_line; i++){
		printf("stringArray[%i]: %s", i, string_array[i]);
	}
}	

int get_file_total_line(char *file_name){
	long file_size;
	FILE *fp;
	fp = fopen(file_name, "r");
	if (fp){
		fseek(fp, 0L, SEEK_END);
		file_size = ftell(fp);

		fseek(fp, 0L, SEEK_SET);

		char *buffer;
		buffer = (char *) malloc(file_size);
		bzero(buffer, file_size);
		fread(buffer, file_size, ELEMENT_NUMBERS, fp);
		
		int total_line = 0;
		for (int i = 0; i < file_size; i++){
			if (buffer[i] == '\n') total_line += 1;
		}
		fclose(fp);
		return total_line+1;
	} else printf("Unable to open file %s\n", file_name);
	return 0;
}