# Build source file and build flags

``gcc main.c`` or ``cc main.c``: Build the whole source file ``main.c`` into ``a.exe`` (Windows) or ``a.out`` (Unix). To run: ``./a.out`` (Unix) or ``./a.exe`` (Windows)

``gcc -o main main.c``: Specify the executable output file as ``main``. 

To run ``a.out`` in absolute path: ``/home/username/Documents/a.out`` (must not have ``./``)

To compile with multiple files (with or even without header file): ``gcc main.c file_1.c file_2.c``

## Compile multiple files when there is no header file

``head.c``

```c
#include <stdio.h>

void display_string(){
	printf("Hello\n");
}
```
``main.c``
```c
#include <stdio.h>

int main(){ 
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

**Using build automation tools**: Compiling many files with GCC like above is not an efficient way, especially when having many source files and many directories. Build automation tools like [Make](https://github.com/TranPhucVinh/Linux-Shell/tree/master/Bash%20script/Build%20automation%20tools/Make) (especially [Makefile for GCC](Makefile%20for%20GCC.md)), [Bazel](https://github.com/TranPhucVinh/Linux-Shell/tree/master/Bash%20script/Build%20automation%20tools/Bazel), [CMake](https://github.com/TranPhucVinh/Linux-Shell/tree/master/Bash%20script/Build%20automation%20tools/CMake) will solve that problem.

# Linker flags

Link a C program with a static/shared library using ``-l``/``-L``:

* ``-l``: Indicates the name of the shared library
* ``-L``: Location of the shared library

E.g: ``gcc httpClient.c -lcurl``

For other usages of ``-L`` and ``-l``, check [static library document](Static%20library.md).

# -static

**-static** flag is used for [static libraries](Static%20library.md), i.e copying all neccessary libraries into the executable file. This flag, along with static libraries, are useful in customized Linux system, e.g a [customized Raspbian with busybox](https://github.com/TranPhucVinh/Raspberry-Pi-GNU/tree/main/Kernel/Build%20Raspbian%20from%20scratch), where those 3 dynamic libraries **linux-vdso**, **libc** and **ld-linux-x86-64** to run a C source file are missing. In this case, compiling the source with with **-static** (**aarch64-linux-gnu-gcc -static main.c**) will help copying all neccessary libraries into the executable file. Reference to [Setup communication between host PC and the Raspberry Pi board containing this customized Raspbian then run a.out file](https://github.com/TranPhucVinh/Raspberry-Pi-GNU/blob/main/Kernel/Build%20Raspbian%20from%20scratch/Implementations.md#setup-communication-between-host-pc-and-the-raspberry-pi-board-containing-this-customized-raspbian-then-run-aout-file) for that implementation.

# Include directory of header files with -I

**General define**: Use this defines to all examples below

``head.h``

```c
int a = 9;
```

``main.c``

```c
#include <stdio.h>
#include "head.h"

int main(){
	printf("%d", a);
}
```

## Include 1 file with the folder hierarchy like below

```
working_folder
|--main
|    |--head.h
|--main.c
```

Inside ``working_folder`` folder, compile ``main.c`` : ``gcc -Imain main.c``

## Include 1 file in the upward folder with the folder hierarchy like below

```
working_folder
|--main
|   |--main.c
|--head.h
```

Inside ``main`` folder, compile ``main.c`` : ``gcc -I.. main.c``

## Include multiple folders

```
working_folder
├── lib1
|   └── lib1.h
├── lib2.h
|   └── lib2.h
└── main.c
```

``head_1.h``

```c
int b = 10;
```

``main.c``

```c
#include <stdio.h>
#include "lib1.h"
#include "lib2.h"

int main(){
	printf("%d %d\n", a, b);
}
```

Inside ``working_folder``, compile ``main.c``: ``gcc -Ilib1 -Ilib2 main.c``

## Header file and source file in different directories

```
working_folder
|--src
|   |--head.c
|--inc
|   |--head.h
|--main.c
```
``head.h``

```c
#include <stdio.h>
void add(int a, int b);
```

``head.c``
```c
#include "head.h"

void add(int a, int b)
{
    printf("I call all files from userspace result: %d\n", a+b);
}
```
``main.c``
```c
#include <stdio.h> 
#include "head.h" 

int main() 
{ 
	add(1,35);
    return 0; 
} 
```

Compile: ``gcc -Iinc -Isrc main.c src/head.c``

# Predefine

``-D``: Define flag

Predefine during compilation with -D flag: Check [Macro document: Using macro to define](../Introduction/Macro/Condition%20in%20macro.md#predefine-during-compilation-using-flag--d).

# Specific steps inside build process

``gcc -S main.c``: Compile source file into assembly code, the output file will be ``main.s``

## Compile and assemble

``gcc -c main.c``: Compile and assemble ``main.c`` into an object file ``main.o``.

**Notice**: Only a ``.c`` file result in a ``.o`` file

``gcc -c test1.c test2.c`` results in ``test.o`` and ``test1.o``.

**Notice**: Cannot specify -o with -c, -S or -E with multiple files

``gcc -c test.c test1.c -o test.o`` will be error

``test.c`` and ``test1.c`` have to be compiled seperatedly for ``test.o`` and ``test1.o``
