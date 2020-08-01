### Change const variable

Change ``const`` variable with ``memset()``

```c
#include <stdio.h>
#include <string.h>

int main(){
   const int a = 10;
   printf("value a before: %d \n", a);// value a before: 10
   memset(&a, 'a', 1);
   printf("value a after: %d \n", a);// value a after: 97 
}
```

**Result**: Compile this will give warning but work as expected