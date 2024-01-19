# fopen()

Open file to read, write, append,...

```c
FILE *fopen(const char *filename, const char *mode)
```

**Example**

```c
FILE *fptr; //file pointer
file = fopen("text.md", "r"); //Open text.md to read
```

**Mode**:

* r: read
* w: write, create the file if not existed
* a: append
* r+: open a file to write and read, file must existed
* w+: open an empty file to write and read
* a+: open a file to read and append
* ``b`` and ``rb``: open non-text files like image

Get the file descriptor value from file pointer with ``fileno()``:

```c
char filePath[] = "test.c";
FILE *fptr; //file pointer
fptr = fopen(filePath, "r");
printf("fileno: %ld\n", fileno(fptr));
```

# fread()

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
```

Read totally ``nmemb*size`` bytes (including ``\n``) of data from ``stream`` and stores to ``ptr``.

* ``ptr``: pointer to a block of memory with a minimum size of ``size*nmemb`` bytes.
* ``size``: size in bytes of each element to be read.
* ``nmemb``: This is the number of elements, each one with a size of size bytes.
* ``stream``: This is the pointer to a ``FILE`` object that specifies an input stream.

```c
#define ELEMENT_NUMBERS 3
#define READ_SIZE 2
#define BUFFER_SIZE 2

FILE *fp;
char buffer[BUFFER_SIZE];

fp = fopen("README.md", "r");

fread(buffer, READ_SIZE, ELEMENT_NUMBERS, fp);//Will read ELEMENT_NUMBERS*READ_SIZE from fp
printf("%s\n", buffer);
fclose(fp);
```

Read 2 entered characters from ``stdin`` and print out

```c
#define READ_SIZE 1
#define BUFFER_SIZE 2

char buffer[BUFFER_SIZE];

while (1){
	fread(buffer, READ_SIZE, BUFFER_SIZE, stdin);//Will read ELEMENT_NUMBERS*READ_SIZE from fp
	printf("%s\n", buffer);
}
```

The difference between:

```c
fread(read_buffer, 1024, 1, fptr);
```
```c
fread(read_buffer, 1, 1024, fptr);
```

Both function read 1024 from ``fptr``, however with ``n = fread(read_buffer, 1, 1024, fptr);``, we can keep on the reading of file by chunk. For example, with a file with size ``1347`` bytes, after reading ``1024``, there are still left ``323``. So we will keep reading the left ``323``. ``n = fread()`` this time will return ``323``. 

Check 2 examples for that implementations

* [Read big file in chunk with read size of each element = 1](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/File%20pointer%20examples.md#read-big-file-in-chunk-with-read-size-of-each-element--1)
* [http_server_returns_beautiful_html_files.c in ESP8266-RTOS-SDK](https://github.com/TranPhucVinh/ESP8266-RTOS-SDK/blob/main/Applicaton%20layer/HTTP/http_server_returns_beautiful_html_files.c)

# fgets()

Read the content in a file or stream until encounter the new line character (``\n``) or until finished reading ``n-1`` character; then store in ``s``.

```c
fgets(char *s, int n, FILE *stream);
```

**Example**: Read an entered string which included space from command line (``stdin``) then prints out on screen

```c
char buf[15];
printf("Enter string: ");
fgets(buf, 15, stdin);// Hello, World !
printf("string is: %s\n", buf);// Hello, World !
```

This will printout the entered string **followed with a new line**, to remove that new line:

```c
char buf[15];
printf("Enter string: ");
fgets(buf, 15, stdin); 
int len=strlen(buf); //where buff is your char array fgets is using
if(buf[len-1]=='\n')	buf[len-1]='\0';
printf("string is: %s\n", buf);
```

**Error with buf[1]**: This will not allow you to enter any string

```c
char buf[1];
printf("Enter string: ");
fgets(buf, 1, stdin); 
printf("string is: %c\n", buf[0]);
```

**Result**: ``Enter string: string is:``

**Problem solve**: Change to ``fgets(buf, 2, stdin)``

```c
char buf[1];
fgets(buf, 2, stdin); 
```

**Note**: As ``fgets()`` is stopped when encountering a newline, it must not be use to read a file including newline. Use [fread()](#fread) instead.

**Error when reading 2 entered string repeatedly**:

# fprintf()

Sends formatted output to a stream.

```c
int fprintf(FILE *stream, const char *format, ...) 
```

**stream**: ``stdin``, ``stdout``, ``stderr``

**Example**: Write content to empty file

```c
FILE *fileptr;
fileptr = fopen("text.md", "w+");
fprintf(fileptr, "Erin");
```

**Example**: Print out string in terminal with ``stdout`` and ``stderr``

```c
fprintf(stdout, "Hello, World! \n");
```
```c
fprintf(stderr, "Hello, World! \n");
```

# fwrite()

```c
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
```

Print out a string to ``stdout``
```c
#define WRITE_SIZE 1

char displayedString[] = "Hello, World !";
fwrite(displayedString , WRITE_SIZE , sizeof(displayedString) , stdout);
```
**Note**: For ``displayedString`` to be displayed inside a ``while()`` loop, it must have a ``\n`` character.

```c
while (1){
	char displayedString[] = "Hello, World !111";
	fwrite(displayedString , WRITE_SIZE , sizeof(displayedString) , stdout);
	delaySeconds(1);
}
```

# fputs()

```c
FILE *fptr;
char displayedString[] = "Hello, World !"
fputs(displayedString, fptr);
```

Print out a string to ``stdout``

```c
fputs("Hello, World ! 1\n", stdout);
```

# fseek()

```c
int fseek( FILE * stream, long int offset, int origin);
```

``fseek()`` sets the file position of the stream to the given offset.

* ``offset``: Number of bytes to offset from origin.
* ``origin``: Position used as reference for the offset. 
	* ``SEEK_SET``:	Beginning of file
	* ``SEEK_CUR``:	Current position of the file pointer
	* ``SEEK_END``:	End of file

# ftell()

```c
long int ftell(FILE *stream);
```
Get current position in ``stream``. Returns the current value of the position indicator of the stream.

**Application**: Use ``fseek()`` and ``ftell()`` to check size of a file then read that file [File pointer example 1](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/File%20pointer%20examples.md#example-1) and [read_file() function in basic_file_operations.c](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/basic_file_operations.c).

# getline()

Delimited string input

```c
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
```

If ``*lineptr`` is ``NULL``, then ``getline()`` will allocate a buffer for storing the line, which should be freed by the user program. (In this case, the value in ``*n`` is ignored.)

Alternatively, before calling ``getline()``, ``*lineptr`` can contain a pointer to a ``malloc()``, allocated buffer ``*n`` bytes in size.

**Example**: Read every line of a file

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;

   	fp = fopen("README.md", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

	while (getline(&line, &len, fp) != -1) {
        printf("%s", line);
    }

   	free(line);
    exit(EXIT_SUCCESS);
}
```
