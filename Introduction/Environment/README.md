### Linux Programmer's Manual

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