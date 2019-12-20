### Open file to read or write.

``fopen()`` Open file to read, write, append,...

```c
FILE *fopen(const char *filename, const char *mode)
```

**Usage**

```c
FILE *fptr; //file pointer
file = fopen("text.md", "<mode>");
```

**Mode**:

* r: read
* w: write
* a: append
* r+: open a file to write and read, file must existed
* w+: open an empty file to write and read
* a+: open a file to read and append
* t
* b

### Example

* ``readFile.c``: Read content from existed files
* ``writeEmptyFile.c``: Write to an empty file, if file already existed, do nothing

### fprintf()

Sends formatted output to a stream.

```c
int fprintf(FILE *stream, const char *format, ...) 
```

**Stream**:

* stdin: stream data in, where data stream is entered
* stdout: stream data out, output data to a stream
* stderr: stream data error

**Example: Write content to empty file**

```c
FILE *fileptr;
fileptr = fopen("text.md", "w+");
fprintf(fileptr, "Erin");
```

**Example: Print out string in terminal with stdout and stderr**

```c
fprintf(stdout, "Hello, World! \n");
```
```c
fprintf(stderr, "Hello, World! \n");
```

### fgets()

```c
fgets(char *s, int n, FILE *stream);
```
read the content in a file  or stream until encounter the new line character ('\n') or until finished reading n-1 character; then store in "s".

```c
fgets(msg, 81, stream);
```

**Example**: Read a string enter in command line (stdin) then print out on screen

```c
#include <stdio.h>
#include <stdlib.h>
 
#define BUFFSIZE 256

int main() {
	char buffer[BUFFSIZE];
    fgets(buffer,BUFFSIZE, stdin);
    puts(buffer);
}
```

**Example: Printout the content inside file "open.c"**

```c
#include <stdio.h>

void main() {
	FILE *stream;
	char msg[81];
	stream = fopen("open.c","r");
	fgets(msg, 81, stream);
	printf("%s\n",msg );
	fclose(stream); // without fclose() still run fine
}
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
	file = fopen("text.abc", "r"); // this can be .md, .txt, ....
	if (file == NULL) {
		perror("Error");
	}
}
```