``size a.out``: displays the size of the text, initialized data, and uninitialized data (bss) segments of binary executable file ``a.out``

# [Embedded command](Embedded%20command.md)

* [system()](Embedded%20command.md#system)
* [popen() and pclose()](Embedded%20command.md#popen-and-pclose)
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
