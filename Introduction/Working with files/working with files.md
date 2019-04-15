### fopen()

Open file to read or write.

**Prototype**

```c
FILE *fopen(const char *filename, const char *mode)
```

**Example**

```c
FILE *file;
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

**Example: Write content to files**

```c
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

### fprintf()

Sends formatted output to a stream.

```c
int fprintf(FILE *stream, const char *format, ...) 
```

**Stream**:

* stdin: stream data in, where data stream is entered
* stdout: stream data out, output data to a stream
* stderr: stream data error

**Example: fprintf() with file**

```c
int main() {
	FILE *file;
	file = fopen("text.md", "w+");
	fprintf(file, "Erin");
}
```

**Example: Print out Hello World in terminal with stdout and stderr**

```c
fprintf(stdout, "Hello, World! \n");
```
```c
fprintf(stderr, "Hello, World! \n");
```
**Result**
```
Hello, World!
```

### perror()

Print out message describe error in ``stderr``.

```c
void perror(const char *str)
```

**Example**

```c
int main() {
	perror("hello");
}
```

**Result**

```
hello: Success
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

```
Error: No such file or directory
```

----------

### fgets()

````c
fgets(char *s, int n, FILE *stream);
````
read the content in file "stream" until encounter the new line character ('\n') or until finished reading n-1 character; then store in "s".

````c
fgets(msg, 81, stream);
````