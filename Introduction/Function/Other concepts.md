# Scope
## Local variable setup with {}

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

## Static scoping

In static scoping (or lexical scoping), definition of a variable is resolved by searching its containing block or function. If that fails, then searching the outer containing block and so on. ``C`` programming language follows static scoping, not dynamic scoping.

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
**Example**: An example of using global and local variables named ``a`` and ``b``.
```c
int a = 10, b = 20;
int add_function(int);
int main() 
{ 
   int a = 5;
   a = add_function(a);    
   printf("a: %d", a);//15
   return 0; 
} 

int add_function(int b){
   /*
      a=10 as using global a
      global variable b is not use, as using local variable b
   */   
   b = b + a;
   return b;
}
```

# Random number generators
``rand()`` and ``srand()`` are defined in ``stdlib.h``

Generate a random number

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Random number %d\n", rand());
    return(0);
}
```

Then the same random number will be generated every time we run the program but different number will be generated if using ``while()`` loop:

```c
while (1){
    printf("Random number %d\n", rand());
	sleep(1);
}
```

To generate a new number every time:

```c
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    srand(time(NULL));
    printf("Random number %d\n", rand());
    return(0);
}
```

Generate a float random number from range:

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOWER 	35
#define UPPER	40

void generate_random_number(float lower, float upper)
{
	float number = (float)rand()/(float)(RAND_MAX) * (upper- lower) + lower;
	printf("%f", number);
}
  
int main()
{ 
    srand(time(0));
  
    generate_random_number(LOWER, UPPER);
  
    return 0;
}
```
