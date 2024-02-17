# Header file

## Define function, variable in ``.h`` file

``header.h``

```c
#include <stdio.h>

void display_string(){
	printf("Hello, World !\n");
}

int value = 6;
```

``main.c``

```c
#include "header.h"

int main(){
	display_string(); //Hello, World !
	printf("%d \n", value); //6
}
```

## Define function inside ``.c`` file

``header.h``

```cpp
#include <stdio.h>

void display_string();
```

``header.c``

```cpp
#include "header.h"

void display_string(){
    printf("Hello, World !\n");
}
```

``main.c``

```c
#include "header.h"

int main(){
	display_string(); //Hello, World !
}
```

For [One definition rule (ODR)](#one-definition-rule-odr), only functions are allowed to be defined inside .c source file. Defining variables inside .c source files causes compilation error, especcially with G++

# One definition rule (ODR)

``head.h``

```c
#include <stdio.h>

int a = 10;
```
``head.c``
```c
#include "head.h"
```

``main.c``

```c
#include "head.h"

int main(){
	printf("%d \n", a);
}
```
Compile  ``gcc main.c head.c`` will give error:

```
/usr/bin/ld: /tmp/cc27NLmt.o:(.data+0x0): multiple definition of `a'; /tmp/ccZ06TNs.o:(.data+0x0): first defined here
collect2: error: ld returned 1 exit status
```
**Note**: This happens as multiple sources like ``main.c``, ``head.c`` includes one ``head.h`` file. If the variable is defined in ``head.h`` and only one source calls it like ``main.c``, the ODR error doesn't happen.

To solve ODR issue, use:

* [extern](README.md#use-extern-to-solve-odr-issue)
* [static](https://github.com/TranPhucVinh/C/blob/master/Introduction/Keywords/static.md#global-static-and-odr)

## Use extern to solve ODR issue

``head.h``

```c
#include <stdio.h>
extern int a;
```
``head.c``
```c
#include "head.h"
int a = 10;
```
``main.c`` kept as above
