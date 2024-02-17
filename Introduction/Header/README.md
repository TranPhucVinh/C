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
## Defining variable inside header files are prohibited due to ODR
**Those implementations break ODR**:

**header.h**

```c
#include <stdio.h>

int a = 10;
```
**header.c**
```c
#include "header.h"
```
**main.c**
```c
#include "header.h"

int main(){
	printf("%d \n", a);
}
```
Compile  ``gcc main.c head.c`` will give error:

```
/usr/bin/ld: /tmp/cc27NLmt.o:(.data+0x0): multiple definition of `a'; /tmp/ccZ06TNs.o:(.data+0x0): first defined here
collect2: error: ld returned 1 exit status
```
## Defining variable inside source files are prohibited due to ODR
**Those implementations break ODR**:
**header.h**
```c
#include <stdio.h>

int a;
```
**header.c**
```c
#include "header.h"

int a = 123;
```

**main.c** is same like above

Compile  ``gcc main.c head.c`` don't give any error while compiling with **g++** gives compilation error.

# Use extern and static to follow ODR
2 above issues happen as multiple sources like ``main.c``, ``header.c`` includes one ``header.h`` file. If the variable is defined in ``header.h`` and only one source calls it like ``main.c``, the ODR error doesn't happen.

To follow ODR rule, use:

* [extern](README.md#use-extern-to-follow-odr)
* [static](https://github.com/TranPhucVinh/C/blob/master/Introduction/Keywords/static.md#global-static-and-odr)

## Use extern to follow ODR

``header.h``

```c
#include <stdio.h>
extern int a;
```
``header.c`` and ``main.c`` are kept unchanged
# pragma once to fix functions redefinition issue
**This implementation causes functions redefinition issue**:
``header_1.h``
```c
#include <stdio.h>

void display_string(){
	printf("Hello, World !\n");
}
```
``header_2.h``
```c
#include "header_1.h"
```
```c
#include "header_1.h"
#include "header_2.h"

int main(){
    display_string();
}
```
**Error**:  ``redefinition of ‘display_string’``

To fix that issue, use **#pragma once** in **header_1.h** to **cause the current header file to be included only once in a single compilation**

**header_1.h**
```c
#pragma once

#include <stdio.h>

void display_string(){
	printf("Hello, World !\n");
}
```
**header_2.h** and **main.c** are kept unchanged
