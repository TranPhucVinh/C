# system()

Run embedded Unix or Windows commands in ``C`` source code

```c
#include <stdlib.h>

main() {
	system("ls"); //Run ls command
}
```

On Windows, the ``a.exe`` of this file will run normally in Git Bash and will result in error ``command not found`` in Command Prompt.

``system("dir");`` will run properly in Command prompt.
# popen() and pclose()

The ``popen()`` function opens a process by creating a pipe, forking, and invoking the shell.

```c
FILE *popen(const char *command, const char *type);
```

The ``command`` argument is a pointer to a null-terminated string containing a shell command line.  This command is passed to ``/bin/sh``, then interpretation, and finally is performed by the shell.

``pclose()`` will close the pipe opened by ``popen()``.

```c
int pclose(FILE *stream);
``` 

``ls`` command

```c
#include <stdio.h>

#define ELEMENT_NUMBERS 1
#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];


int main(){
    FILE* pipe = popen("ls", "r");
    fread(buffer, BUFFER_SIZE, ELEMENT_NUMBERS, pipe);//Will read ELEMENT_NUMBERS*READ_SIZE from fp
    printf("%s\n", buffer);
    pclose(pipe);
}
```

``rm`` command:

```c
FILE* pipe = popen("rm a.out", "r");
pclose(pipe);
```
