``size a.out``: displays the size of the text, initialized data, and uninitialized data (bss) segments of binary executable file ``a.out``

# [Embedded command](Embedded%20command.md)

## system()

Run embedded Unix or Windows commands in ``C`` source code

```c
#include <stdlib.h>
int system(const char *command);
```
**Return**
* ``-1``: Error
* Status number of command when sucess
**Example**:
```c
system("ls"); //Run ls command
```

On Windows, the ``a.exe`` of this file will run normally in Git Bash and will result in error ``command not found`` in Command Prompt.

``system("dir")`` will run properly in [Windows Command prompt](https://github.com/TranPhucVinh/Windows-Batch).

[Use system() to start and kill a background job, which includes while(1) loop](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process/Background%20job):
* [Use system() to start a background job which includes a while(1) loop]()
* [Kill the infinite background job by signal]()
* [Run the infinite background job, get its PID then kills it by functions inside in the parent process]()
## popen() and pclose()
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

# Interrupt and ISR

**Can we use printf() inside ISR ?**: ``printf()`` function in ISR is not supported because ``printf()`` function is not reentrant, thread safe and uses dynamic memory allocation which takes a lot of time and can affect the speed of an ISR up to a great extent.

**Can we put breakpoint inside ISR ?**: Putting a break point inside ISR is not a good idea because debugging will take some time and a difference of half or more seconds will lead to different behavior of hardware. To debug ISR, definitive logs are better.

# Environment API

## printenv()

Get environment variable with ``printenv()``. ``environ`` is defined as a global variable in the ``Glibc`` source file ``posix/environ.c`` so this program just runs on Unix.

```c
#include <stdio.h>

extern char **environ;
int main(int argc, char *argv[])
{
    int count = 0;

    printf("\n");
    while(environ[count] != NULL)
   {
         printf("[%s] :: ", environ[count]);
         count++;
   }

   return 0;
}
```
## Get variable environment

``char *getenv(const char *name)`` searches for the environment string pointed to by name and returns the associated value to the string.

This run on both Windows and Unix.

```c
#include <stdio.h>
#include <stdlib.h>

int main () {
   printf("PATH : %s\n", getenv("PATH"));
   printf("HOME : %s\n", getenv("HOME"));
   printf("ROOT : %s\n", getenv("ROOT"));

   return(0);
}
```
