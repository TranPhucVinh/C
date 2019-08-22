## Redefine macro variable

**head.h**

```c
#define integerValue 190
```

**main.c**

```c
#include <stdio.h>
#include "head.h"

int main (){
  printf("%d \n", integerValue);
  #undef integeValue
  #define integerValue 100
  printf("%d \n", integerValue);
}
```

**Result**

```
190
100
```