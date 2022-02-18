GCC is a compiler system that supporting various programming languages.

``gcc main.c``: Compile, assemble and link source file ``main.c`` into ``a.exe`` (Windows) or ``a.out`` (Unix)

``gcc -S main.c``: Build C source code (High level language) to assembly code, the output file will be ``main.s``

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

### For object file

``gcc -c main.c``: Compile and assemble ``main.c`` into an object file ``main.o``.

**Notice**: Only a ``.c`` file result in a ``.o`` file

``gcc -c test1.c test2.c`` results in ``test.o`` and ``test1.o``.

**Notice**: Cannot specify -o with -c, -S or -E with multiple files

``gcc -c test.c test1.c -o test.o`` will be error

``test.c`` and ``test1.c`` have to be compiled seperatedly for ``test.o`` and ``test1.o``

## External libraries

To compile with an external library ``gcc main.c -l<external-library-name>``

E.g: ``gcc httpClient.c -lcurl``

### Include files

``-I``: include files

**Example 1**: Include 1 file

In folder ``test``, there is ``test.h``

```c
int a = 9;
```

In folder ``test/main``, there is ``test.c``

```c
#include <stdio.h>
#include "test.h"

int main(){
	printf("%d", a);
}
```

To compile ``test.c``: ``gcc -I.. test.c``

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
