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
