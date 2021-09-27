### Local variable setup with {}

```c
#include <stdio.h>

int a = 20;
int main(int argc, char *argv[])
{
   {
      int a = 10;
      printf("%d \n", a); //10: local variable
   }
   printf("%d", a); //20: global variable
   return 0;
}
```

### Static scoping

In static scoping (or lexical scoping), definition of a variable is resolved by searchig its containing block or function. If that fails, then searching the outer containing block and so on.

```c
int a = 10, b = 20;
int main() 
{ 
   int a = 5;
   {
      int c;
      c = b/a;
      printf("%d", c);//4
   }      
   return 0; 
} 
```