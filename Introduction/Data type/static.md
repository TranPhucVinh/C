### static global variable

**Static global variables** are not visible outside of the C file they are defined in.

### static local variable

**Static defined local variables** do not lose their value between function calls. In other words they are global variables, but scoped to the local function they are defined in.

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

**Static functions** are not visible outside of the C file they are defined in.