### fopen()

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
* t
* b

Get the file descriptor value from file pointer with ``fileno()``:

```c
char filePath[] = "test.c";
FILE *fptr; //file pointer
fptr = fopen(filePath, "r");
printf("fileno: %ld\n", fileno(fptr));
```

### fprintf()

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

### fread()

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
```

Read totally ``nmemb*size`` bytes (including ``\n``) of data from ``stream`` and stores to ``ptr``.

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

### fwrite()

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

### fgets()

Read the content in a file or stream until encounter the new line character (``\n``) or until finished reading ``n-1`` character; then store in ``s``.

```c
fgets(char *s, int n, FILE *stream);
```

**Example**: Read an entered string which included space from command line (``stdin``) then prints out on screen

```c
char buf[15];
printf("Enter string: ");
fgets(buf, 15, stdin); 
printf("string is: %s\n", buf);
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

### fputs()

```c
FILE *fptr;
char displayedString[] = "Hello, World !"
fputs(displayedString, fptr);
```

Print out a string to ``stdout``

```c
fputs("Hello, World ! 1\n", stdout);
```

### rename()

Rename a file

```c
int rename(const char *old_filename, const char *new_filename)
```

**Return**: ``0`` if rename successfully, ``1`` if unable to rename file

### remove()

Remove a file

```c
int remove(const char *filename);
```

### perror()

Print out message describe error in ``stderr``.

```c
void perror(const char *str)
```

**Example**

```c
int main() {
	perror("hello"); //hello: Success
}
```

**Example: No such file or directory**

```c
int main() {
	FILE *file;
	file = fopen("text.abc", "r");
	if (file == NULL) {
		perror("Error");//Error: No such file or directory
	}
}
```

### fseek()

```c
int fseek( FILE * stream, long int offset, int origin);
```

* ``offset``: Number of bytes to offset from origin.
* ``origin``: Position used as reference for the offset. 

	* ``SEEK_SET``:	Beginning of file
	* ``SEEK_CUR``:	Current position of the file pointer
	* ``SEEK_END``:	End of file

### ftell()

```c
long int ftell ( FILE * stream );
```
Get current position in ``stream``. Returns the current value of the position indicator of the stream.