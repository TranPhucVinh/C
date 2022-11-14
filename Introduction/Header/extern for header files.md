## Problem when compiling CPP files for C main source code

```sh
├── main.c
├── head.cpp
├── head.h
```

``main.c``

```c
#include "head.h"

int main(){
	display_string();
}
```

``head.cpp``

```c
#include "head.h"

void display_string(){
    printf("Work with shared library instead of static library\n");
}
```

If using that ``head.h`` define

```c
#include <stdio.h>

void display_string();
```

(Compile as usual: ``gcc main.c head.cpp``)

Then there will be error:

```
/usr/bin/ld: /tmp/ccly6e0Q.o: in function `main':
main.c:(.text+0xe): undefined reference to `display_string'
collect2: error: ld returned 1 exit status
```

### Problem solved

That happens as C does not support function overloading. When wrapping C API in an ``extern "C"`` construct in C header file, it will force the C++ compiler use C-style call convention for the functions contained the ``extern`` scope.

``head.h``

```c
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    void display_string();
#ifdef __cplusplus
}
#endif  
```

## Problem when compiling C files for CPP main source code

```sh
├── main.cpp
├── head.c
├── head.h
```

``main.cpp`` define kept like ``main.c``

``head.c`` define kept lile ``head.cpp``

If still using that ``head.h`` define

```c
#include <stdio.h>

void display_string();
```

(Compile as usual: ``gcc main.c head.cpp``)

Then there will be error:

```
/usr/bin/ld: /tmp/ccAIrUEs.o: in function `main':
main.cpp:(.text+0x9): undefined reference to `display_string()'
collect2: error: ld returned 1 exit status
```

Problem solved: Solve like **Problem when compiling CPP files for C main source code**.

## Mismatch issue when compiling CPP main source code from static or dynamic libraries built from C files

That issue happens when:

* Main source code is ``main.cpp`` while ``.a``/``.so`` is built from ``.c`` files
* Using the ``head.h`` defined which caused 2 error above

Problem solved: Solve like **Problem when compiling CPP files for C main source code**.

That solution is useful when including the Debian package with ``.h`` and ``.a``/``.so`` file built from C compiler to the CPP source code, e.g [libi2c-dev package](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Bash%20script/Install%20package.md#install-new-package) with ``i2c/smbus.h``. By default after installing, ``i2c/smbus.h`` won't support compiling with CPP source code.

In that case, use the ``extern`` solution like above to ``i2c/smbus.h``. 
