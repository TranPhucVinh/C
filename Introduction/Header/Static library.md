## Fundamental concepts

![](../../Environment/Images/static_library.png)

## Implementation

``head.h``

```c
#include <stdio.h>

void display_string();
```
``head.c``
```c
#include "head.h"

void display_string(){
    printf("Hello World !\n");
}
```

Compile and assemble ``head.c`` into an object file ``head.o``: ``gcc -c head.c``

Archive ``head.o`` to ``head.a`` as a static library: ``ar r head.a head.o``

``main.c``

```c
#include "head.h"

int main(){
	displayString(); //Hello World
}
```

Compile ``main.c`` to ``main.o``: ``gcc -c main.c``

Link static library in the final build for ``a.out``:

```sh
gcc main.c -L. -l:head.a
```

``-L.``: State that static library is in current folder

If there is any later change in ``head.c``, ``head.o`` then has to be built again.
