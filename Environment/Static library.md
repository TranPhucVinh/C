# Fundamental concepts

![](../Environment/Images/static_library.png)

Static libraries are copied by a linker during the creation of the executable file, i.e they're built into the executable file. By using static libraries, executable files will have all neccessarry libraries and don't need to call for any libraries in the system like **shared**/[dynamic libraries](Shared%20library.md).

As having all static libraries built into, an executable file built with static libraries will have a bigger size than the shared libraries ones. (i.e ``a.out`` of ``gcc -static main.c`` has bigger size than its corresponding in shared library ``gcc main.c``)

For a "Hello, World" a.out program compiled with ``-static`` flag for static library ``gcc -static main.c``, all 3 libraries **linux-vdso**, **libc** and **ld-linux-x86-64** are built into it. 

Using static libraries are useful in customized Linux system, e.g a [customized Raspbian with busybox](https://github.com/TranPhucVinh/Raspberry-Pi-GNU/tree/main/Kernel/Build%20Raspbian%20from%20scratch), where those 3 dynamic libraries are missing. In this case, compiling the source with with [-static](GCC%20compiler.md#-static) (**aarch64-linux-gnu-gcc -static main.c**) will help copying all neccessary libraries into the executable file. Refer to [Setup communication between host PC and the Raspberry Pi board containing this customized Raspbian then run a.out file](https://github.com/TranPhucVinh/Raspberry-Pi-GNU/blob/main/Kernel/Build%20Raspbian%20from%20scratch/Implementations.md#setup-communication-between-host-pc-and-the-raspberry-pi-board-containing-this-customized-raspbian-then-run-aout-file) for that implementation.

Static library filenames usually have ``.a`` extension on Unix-like systems and ``.lib`` extension on Microsoft Windows.

# Implementation

## Static lib for header and source files

```
|--main.c
|--header.h
|--header.c
```

``header.h``

```c
#include <stdio.h>

void display_string();
```
``header.c``
```c
#include <stdio.h>//Dont' need to call header.h

void display_string(){
    printf("Hello World !\n");
}
```
By using static library, ``header.c`` will define function ``display_string()`` and doesn't need to include ``header.h``.

### main.c

```c
#include "header.h"//Call header.h for display_string()

int main(){
	display_string(); //Hello World
}
```

## Compilation steps

Compile and assemble ``head.c`` into an object file ``head.o``: ``gcc -c header.c``

Archive ``head.o`` to ``head.a`` as a static library: ``ar r header.a header.o``

Link static library in the final build for ``a.out``:

```sh
gcc main.c -L. -l:header.a
```

``-L.``: State that static library is in current folder

With ``-l:`` flag, the static library can have any type like ``.xyz`` and will give normal result:

```sh
ar r static_lib.xyz header.o
gcc test.c -L. -l:static_lib.xyz
```

It's better to name the static library to ``libheader.a`` so that flag ``-lheader`` can be used. ``-lhead`` will then find ``libheader.a`` in the folder specified by ``-L``.

```sh
ar r libheader.a head.o
gcc test.c -L. -lheader
```

If there is any later change in ``header.c``, ``header.o`` then has to be built again.
## Static lib as a single source file
Single ``header.c`` file can be used by ``main.c`` for function ``display_string()`` in the example above:

``main.c``

```c
#include <stdio.h>

void display_string();

int main(){
	display_string(); //Hello World
}
```
``header.c`` kept as above. Take all steps like above to build ``libhead.a`` then link the static lib.

**Note**

1. For Mismatch issue when compiling CPP main source code from static or dynamic libraries built from C files, check [extern for header files document to solve that issue](https://github.com/TranPhucVinh/C/blob/master/Introduction/Header/extern%20for%20header%20files.md).

2. If using ``g++``, it should be ``g++ -c head.c`` then ``g++ main.c -L. -l:head.a``. Using the ``head.a`` built from ``gcc`` for ``g++`` will result in error:

```
/usr/bin/ld: /tmp/cc2XwWip.o: in function `main':
test.c:(.text+0x9): undefined reference to `display_string()'
collect2: error: ld returned 1 exit status
```

## Build multiple source files into a static library

Check [Makefile to build multiple source files into a static library](#multiple-source-files).

# Makefile

## Single source file

A Makefile to build a static library and run the main source file including it.

[main.c](#mainc) and ``head.c`` are like above.

```Makefile
main: build_src_file main.c
	@(ar r libhead.a head.o)
	@(gcc main.c -L. -lhead)
	@(./a.out)

build_src_file: head.c
	@(gcc -c head.c)
	
clean: #clean target to clean up files
	@(rm *.exe *.o *.out *.a)
```
## Multiple source files

Build a static library from multiple source files

``head1.c``
```c
#include <stdio.h>

void head1(){
    printf("head1\n");
}
```
``head2.c``
```c
#include <stdio.h>

void head2(){
    printf("head2\n");
}
```
``main.c``
```c
#include <stdio.h>

void head1();
void head2();

int main(){
	head1();
	head2();
}
```
```Makefile
main: build_src_file main.c
	@(ar r libhead.a head1.o head2.o)
	@(gcc main.c -L. -lhead)
	@(./a.out)

build_src_file: head1.c head2.c
	@(gcc -c head1.c)
	@(gcc -c head2.c)

clean:
	@(rm *.exe *.o *.out *.a)
```
