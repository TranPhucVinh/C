## Example 1

Check size of a file then read that file:

```c
#include <stdio.h>
#include <stdlib.h>

#define ELEMENT_NUMBERS 1
long file_size;

char file_name[] = "test.c";
int main(int argc, char *argv[]) {
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
		printf("%s\n", buffer);
	} else printf("Unable to open file %s\n", file_name);
}	
```

Using ``sys/stat.h``:

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define ELEMENT_NUMBERS 1
long file_size;

int main(int argc, char *argv[]) {
   struct stat statBuffer;
   char filePath[] = "README.md";

   if (!stat(filePath, &statBuffer)){
      long fileSize = statBuffer.st_size;
      char *buffer;
      buffer = (char *) malloc(fileSize);
      FILE *fp;
      fp = fopen(filePath, "r"); //Open text.md to read
      fread(buffer, fileSize, ELEMENT_NUMBERS, fp);//Will read ELEMENT_NUMBERS*READ_SIZE from fp
      printf("%s\n", buffer);
   }   
}	
```

Read big file in chunk with read size of each element = 1.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fptr;
    fptr = fopen("README.md", "r");
    if (fptr == NULL) {
		printf("Unable to open file\n");
	} else {
        int n = 0;
        char* read_buffer;
        read_buffer = (char*)malloc(1024);
        do
        {
            bzero(read_buffer, 1024);
            n = fread(read_buffer, 1, 1024, fptr);
            printf("%s", read_buffer);
        } while (n > 0);
        printf("\n");
        free(read_buffer);
        fclose(fptr);
    }
}
```

This method helps reading big file by chunk and perform small operation every small chunk. Check ``http_server_returns_beautiful_html_files.c`` in ``ESP8266-RTOS-SDK`` as file like image can only by read by chunk and is returned as small HTTP chunk by the HTTP server to HTTP client. Reading the whole image file at one time and returns it to the HTTP client will result in the failure image or the error image.

## Other examples

``basic_file_operations.c``: Basic operation with file

* Read content of a file
* Create a new file
* Write data to a file
* Delete an existed file
* List all file in the directory

``read_all_files.c``: Read all files of a directory then store inside a dynamic string array