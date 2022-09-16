## Fundamental concepts

![](../../Environment/Images/static_library.png)

## Implementation

### Source code

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

### Compilation steps

Compile and assemble ``head.c`` into an object file ``head.o``: ``gcc -c head.c``

Archive ``head.o`` to ``head.a`` as a static library: ``ar r head.a head.o``

Compile ``main.c`` to ``main.o``: ``gcc -c main.c``

Link static library in the final build for ``a.out``:

```sh
gcc main.c -L. -l:head.a
```

``-L.``: State that static library is in current folder

If there is any later change in ``head.c``, ``head.o`` then has to be built again.

If using ``g++``, it should be ``g++ -c head.c`` then ``g++ main.c -L. -l:head.a``, using the ``head.a`` built from ``gcc`` for ``g++`` will result in error:

```
/usr/bin/ld: /tmp/cc2XwWip.o: in function `main':
test.c:(.text+0x9): undefined reference to `display_string()'
collect2: error: ld returned 1 exit status
```

Error with invalid format as compiling with different compiler (``gcc``) doesn't happen in this case.
