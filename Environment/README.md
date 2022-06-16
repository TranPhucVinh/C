# Software development environment in this repository

Main OS: Ubuntu 16.04

Other OS:
* Windows (specifically noted on any software that are built on Windows)
* WSL Unbuntu 18.04

## Fundamental concepts

Bare metal application

![](../Environment/Images/bare_mental_application.PNG)

OS-based application

![](../Environment/Images/os_based_application.PNG)

## Linux environment

**Linux Programmer's Manual**

Manual document for functions prototype can be accessed by ``man function_prototype``.

E.g: ``man scanf``

### nm

List symbols from object files

```sh
nm a.out
```

### Shell script to compile

```shell
{
  "cmd" : ["gcc", "$file_name", "-o", "${file_base_name}", "-lm", "-Wall"],
  "selector" : "source.c"
  "shell":false,
  "working_dir" : "$file_path"
}
```

## API

### printenv()

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
