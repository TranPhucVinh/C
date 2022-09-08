The **GNU Compiler Collection** (**GCC**) is a compiler system produced by the GNU Project supporting various programming languages. GCC is a key component of the GNU toolchain.

# Build source file

``gcc main.c``: Build the whole source file ``main.c`` into ``a.exe`` (Windows) or ``a.out`` (Unix)

``gcc -o main main.c``: Specify the executable output file as ``main``. To run: ``./main``

To compile with multiple files (with or even without header file): ``gcc main.c file_1.c file_2.c``

Compile with multiple files when there is no header file:

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
Compile: ``gcc main.c head.c``

This gives warning but work normally:
```
main.c:4:5: warning: implicit declaration of function ‘display_string’ [-Wimplicit-function-declaration]
     display_string();
```
Compile those files on G++ gives error: ``gcc main.c head.c``

```
main.c:4:19: error: ‘display_string’ was not declared in this scope
     display_string();
```

**Using build automation tools**: Compiling many files with GCC like above is not an efficient way, especially when having many source files and many directories. Build automation tools like Make, Bazel,... will solve that problem.

## External libraries

To compile with an external library ``gcc main.c -l<external-library-name>``

E.g: ``gcc httpClient.c -lcurl``

## Include directory of header files with ``-I``

**Example 1**: Include 1 file with the folder hierarchy like below

```
working_folder
|--main
	|--main.c
|--head.h
```

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

Inside ``main`` folder, compile ``main.c`` : ``gcc -I.. main.c``

**Example 2**: To include many files

In another folder ``test/test 1``, there is ``test1.h``

```c
int b = 10;
```

In folder ``test/main``, there is ``test.c``

```c
#include <stdio.h>
#include "test.h"
#include "test1.h"

int main(){
	printf("%d", a);
  printf("%d", b);
}
```

To compile ``test.c``: `` gcc -I.. -I../test\ 1 test.c``

## Predefine

``-D``: Define flag

Predefine during compilation with -D flag: Check [Macro document: Using macro to define](https://github.com/TranPhucVinh/C/blob/master/Introduction/Macro/Using%20macro%20to%20define.md).

## Optimizations

Optimizations flags: ``-O``, ``-O1``, ``-O2``, ``-O3``.

# Specific steps inside build process

``gcc -S main.c``: Compile source file into assembly code, the output file will be ``main.s``

### Compile and assemble

``gcc -c main.c``: Compile and assemble ``main.c`` into an object file ``main.o``.

**Notice**: Only a ``.c`` file result in a ``.o`` file

``gcc -c test1.c test2.c`` results in ``test.o`` and ``test1.o``.

**Notice**: Cannot specify -o with -c, -S or -E with multiple files

``gcc -c test.c test1.c -o test.o`` will be error

``test.c`` and ``test1.c`` have to be compiled seperatedly for ``test.o`` and ``test1.o``

# Compilers developed from GCC

* With AVR, we have ``AVR-GCC ``is a part of GCC and support compiling C program for AVR microcontrollers.
* ESP8266 core includes an ``xtensa gcc toolchain``.
