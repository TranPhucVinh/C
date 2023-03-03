# Fundamental concepts

![](../Environment/Images/static_library.png)

Static library filenames usually have ``.a`` extension on Unix-like systems and ``.lib`` extension on Microsoft Windows.

# Implementation

## Source code

```
|--main.c
|--head.h
|--head.c
```

``head.h``

```c
#include <stdio.h>

void display_string();
```
``head.c``
```c
#include <stdio.h>//Dont' need to call head.h

void display_string(){
    printf("Hello World !\n");
}
```

``main.c``

```c
#include "head.h"

int main(){
	display_string(); //Hello World
}
```

By using static library, ``head.c`` will define function ``display_string()`` and doesn't need to include ``head.h``.

## Compilation steps

Compile and assemble ``head.c`` into an object file ``head.o``: ``gcc -c head.c``

Archive ``head.o`` to ``head.a`` as a static library: ``ar r head.a head.o``

Link static library in the final build for ``a.out``:

```sh
gcc main.c -L. -l:head.a
```

``-L.``: State that static library is in current folder

With ``-l:`` flag, the static library can have any type like ``.xyz`` and will give normal result:

```sh
ar r static_lib.xyz head.o
gcc test.c -L. -l:static_lib.xyz
```

It's better to name the static library to ``libhead.a`` so that flag ``-lhead`` can be used. ``-lhead`` will then find ``libhead.a`` in the folder specified by ``-L``.

```sh
ar r libhead.a head.o
gcc test.c -L. -lhead
```

If there is any later change in ``head.c``, ``head.o`` then has to be built again.

Single ``head.c`` file can be used by ``main.c`` for function ``display_string()`` in the example above:

``main.c``

```c
#include <stdio.h>

void display_string();

int main(){
	display_string(); //Hello World
}
```
``head.c`` kept as above.

**Note**

1. For Mismatch issue when compiling CPP main source code from static or dynamic libraries built from C files, check [extern for header files document to solve that issue](https://github.com/TranPhucVinh/C/blob/master/Introduction/Header/extern%20for%20header%20files.md).

2. If using ``g++``, it should be ``g++ -c head.c`` then ``g++ main.c -L. -l:head.a``, using the ``head.a`` built from ``gcc`` for ``g++`` will result in error:

```
/usr/bin/ld: /tmp/cc2XwWip.o: in function `main':
test.c:(.text+0x9): undefined reference to `display_string()'
collect2: error: ld returned 1 exit status
```

Error with invalid format as compiling with different compiler (``gcc``) doesn't happen in this case.
