``extern`` function defined works normally with header files.

``head.h``

```c
#include <stdio.h>
extern int returnInt();
```

``head.c``

```c
#include "head.h"

int returnInt(){
   return 4;
}
```

``main.c``

```c
#include "head.h"

int main(){
   printf("%d ", returnInt());
}
```