## Example 1

Check size of a file then read that file:

```c
#include <stdio.h>
#include <stdlib.h>

#define ELEMENT_NUMBERS 1
long file_size;

int main(int argc, char *argv[]) {
   FILE *fp;
   fp = fopen("test.c", "r"); //Open text.md to read
   fseek(fp, 0L, SEEK_END);
   file_size = ftell(fp);

   fseek(fp, 0L, SEEK_SET);

   char *buffer;
   buffer = (char *) malloc(file_size);
   fread(buffer, file_size, ELEMENT_NUMBERS, fp);//Will read ELEMENT_NUMBERS*READ_SIZE from fp
   printf("%s\n", buffer);
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

## Other examples

``read_and_store.c``: Read 10 bytes data from every line of file ``json.txt`` then store in an array string

``basic_file_operations.c``: Basic operation with file

* Read content of a file
* Create a new file
* Write data to a file
* Delete an existed file
* List all file in the directory

### Notes

``json.txt``

```
170604d9cc
180604d9cc
1e0604d9cd
```

**Notice**: For 10 bytes data and a new line (``\n``) to read in ``fgets()``, the read buffer must be 12 bytes (for ``n-1`` byte read).