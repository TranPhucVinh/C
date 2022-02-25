# static variable

**Static variables** is used to created variable that are visible to only one function, but unlike local variables that get created and destroyed everytime a function is called, static variables do not lose their value between function calls.

```c
#include <stdio.h> 

int fun(){ 
  int static count = 0; 
  count++;
  return count; 
} 
   
int main(){ 
   printf("%d ", fun()); 
   printf("%d ", fun()); //count remains its value after 1st time call func()
   return 0; 
}
```

**Result**

``1 2``

**static variable** can be shared normally between headers files and source files.

``head.h``

```c
#include <stdio.h>
static int a = 10;
```
``main.c``
```c
#include "head.h"

int main(){ 
    printf("a: %d", a);
}
```

## Internal linkage

To share value between 2 C source files, use internal linkage as including the C files:

``test.c``

```c
#include <stdio.h>
  
static int a = 123;
```

``main.c``

```c
#include <stdio.h>
#include "test.c"

int main(void)
{
	printf("%d", a);
}
```

If not using ``static``, there will be error: 

```
/tmp/ccO9p8dN.o:(.data+0x0): multiple definition of `a'
/tmp/ccsaapP6.o:(.data+0x0): first defined here
collect2: error: ld returned 1 exit status
```

# static function

**Static functions** are not visible outside of the object file they are defined in.

**Example**

``head.h``

```c
#include <stdio.h>

static void displayString();
```

``head.c``

```c
#include "head.h"

static void displayString(){
	printf("Hello, World !\n");
}
```

``main.c``

```c
#include "head.h"

int main(){ 
    displayString();
}
```

When compiling, there will be error: 

```
main.c:(.text+0x5): undefined reference to `displayString()'
```
