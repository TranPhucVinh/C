# Build source file

``gcc main.c`` or ``cc main.c``: Build the whole source file ``main.c`` into ``a.exe`` (Windows) or ``a.out`` (Unix). To run: ``./a.out`` (Unix) or ``./a.exe`` (Windows)

``gcc -o main main.c``: Specify the executable output file as ``main``. 

To run ``a.out`` in absolute path: ``/home/username/Documents/a.out`` (must not have ``./``)

To compile with multiple files (with or even without header file): ``gcc main.c file_1.c file_2.c``

## Compile multiple files when there is no header file

``head.c``

```c
#include <stdio.h>

void display_string() {
	printf("Hello\n");
}
```
``main.c``
```c
#include <stdio.h>

int main() { 
    display_string();
}
```
Compile: ``gcc main.c head.c`` or ``g++ main.c head.c``

This gives warning on GCC but error on G++:

```
main.c:4:19: error: ‘display_string’ was not declared in this scope
     display_string();
```

To solve that problem, add ``display_string()`` in ``main.cpp``:

```c
#include <stdio.h>
void display_string();
int main(){ 
    display_string();
}
```

This implementation is useful when we need to perform [external linkage](https://github.com/TranPhucVinh/C/blob/master/Introduction/Linkage.md#external-linkage).

## Using build automation tools

Compiling many files with GCC like above is not an efficient way, especially when having many source files and many directories. Build automation tools like [Make](https://github.com/TranPhucVinh/Linux-Shell/tree/master/Bash%20script/Build%20automation%20tools/Make) (especially [Makefile for GCC](Makefile%20for%20GCC.md)), [Bazel](https://github.com/TranPhucVinh/Linux-Shell/tree/master/Bash%20script/Build%20automation%20tools/Bazel), [CMake](https://github.com/TranPhucVinh/Linux-Shell/tree/master/Bash%20script/Build%20automation%20tools/CMake) will solve that problem.

# Specific steps inside build process

``gcc -S main.c``: Compile source file into assembly code, the output file will be ``main.s``

## Compile and assemble

``gcc -c main.c``: Compile and assemble ``main.c`` into an object file ``main.o``.

**Notice**: Only a ``.c`` file result in a ``.o`` file

``gcc -c test1.c test2.c`` results in ``test.o`` and ``test1.o``.

**Notice**: Cannot specify -o with -c, -S or -E with multiple files

``gcc -c test.c test1.c -o test.o`` will be error

``test.c`` and ``test1.c`` have to be compiled seperatedly for ``test.o`` and ``test1.o``
# Get libc version

```c
#include <gnu/libc-version.h>
printf("%s\n", gnu_get_libc_version());
```