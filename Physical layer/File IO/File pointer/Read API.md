# fopen()

Open file to read, write, append,... Return a file pointer

```c
FILE *fopen(const char *filename, const char *mode)
```
<details>
	
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

</details>

# fileno()
Return the file descriptor value from file pointer

```c
char filePath[] = "README.md";
FILE *fptr; //file pointer
fptr = fopen(filePath, "r");
printf("fd: %d\n", fileno(fptr));
```

# fread()

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
```

Read totally ``nmemb*size`` bytes (including ``\n``) of data from ``stream`` and stores to ``ptr``.

* ``ptr``: pointer to a block of memory with a minimum size of ``size*nmemb`` bytes.
* ``sz``: size in bytes of each element to be read.
* ``nmemb``: This is the number of elements, each one with a size of ``sz`` bytes.
* ``stream``: This is the pointer to a ``FILE`` object that specifies an input stream.
  
<details>

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

</details>

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
# fdopen()
Associate a file pointer from a file descriptor
```c
#include <stdio.h>
#include <unistd.h> //for read()
#include <fcntl.h> //for open()

#define ELEMENT_NUMBERS 1
#define READ_SIZE       100
#define BUFFER_SIZE     100

int main(){
    char buffer[BUFFER_SIZE];
    FILE *fptr;

    int fd = open("README.md", O_RDONLY);
    fptr = fdopen(fd, "r");
    fread(buffer, READ_SIZE, ELEMENT_NUMBERS, fptr);//Will read ELEMENT_NUMBERS*READ_SIZE from fp
    printf("%s\n", buffer);
    fclose(fptr);
    close(fd);
}
```
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

However. this method results in **Error when reading entered character into buf[1]**:
```c
#include <stdio.h> 

#define SIZE 50

int main() 
{ 
    char ch[1], s[SIZE];

    fgets(ch, 2, stdin);
    printf("%c", ch[0]);

	// Same result with:
	// fgets(ch, 2, stdin);
    // printf("%s", ch);

    fgets(s, SIZE, stdin);
    printf("%s", s);

	printf("Program ends\n");
} 
```
**Result**
```
a
a
Program ends
```
(``fgets(s, SIZE, stdin)`` won't be called).

**Problem solved**: Use [readline()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/realloc_string_entered.c#L13) function from [realloc_string_entered.c](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/realloc_string_entered.c) which includes memoization of fgets().

**Note**: As ``fgets()`` is stopped when encountering a newline, it must not be use to read a file including newline. Use [fread()](#fread) instead.

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
