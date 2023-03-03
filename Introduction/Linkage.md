# Fundamental concepts

Identifiers like variables and functions have another property named linkage. An identifier’s linkage determines whether other declarations of that name refer to the same object or not.

There are 3 types of linkage:
* No linkage
* [Internal linkage](#internal-linkage)
* [External linkage](#external-linkage)

Local variables have **no linkage**, which means that each declaration refers to a unique object. 

Global variable and functions identifiers can have either **internal linkage** or **external linkage**. 

# Internal linkage

An identifier with internal linkage can be seen and used within a single file, but it is not accessible from other files (that is, it is not exposed to the linker). This means that if two files have identically named identifiers with internal linkage, those identifiers will be treated as independent.

Global variables are treated as internal linkage

To link variable from a source file to the main file, include that file in the main file as internal linkage.

``header.c``

```c
#include <stdio.h>

int a = 123;
void display_string()
{
    printf("Hello, World !\n");
}
```

``main.c``

```c
#include <stdio.h>
#include "head.c"

int main()
{
    display_string();//Hello, World !
    printf("%d\n", a);//123
    return 0;
}
```
Compile: ``gcc main.c``

If compile ``gcc main.c head.c``, there will be error:

```
multiple definition of `display_string'
ld returned 1 exit status
```

# External linkage

An identifier with external linkage can be seen and used both from the file in which it is defined, and from other code files

``header.c``

```c
#include <stdio.h>

int a = 123;
void display_string()
{
    printf("Hello, World !\n");
}
```
``main.c``
```c
#include <stdio.h>

int display_string(void);
extern int a;
int main()
{
    display_string();//Hello, World !
    printf("%d\n", a);//123
    return 0;
}
```
Compile those 2 files normally to access ``display_string()`` and ``int a`` in ``main.c``: ``gcc main.c header.c``
