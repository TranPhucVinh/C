### printenv()

Get environment variable with ``printenv()``. ``environ`` is defined as a global variable in the Glibc source file ``posix/environ.c`` (so this program just runs on Unix).

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

### Get variable environment

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