### static variable

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

### static function

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