# Scope
## Local variable setup with {}

```c
#include <stdio.h>

int a = 20;
int main()
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
int main() { 
   int a = 5;
   a = add_function(a);    
   printf("a: %d", a);// 25
   return 0; 
} 

int add_function(int a) {
   /*
      b = 20 as using global b
      global variable a is not use, as using local variable a
   */   
   a = b + a;
   return a;
}
```
# Get function name with ``__FUNCTION__``, ``__func__`` and ``__PRETTY_FUNCTION__``:

```c
void displayString(){
	printf("%s\n",  __FUNCTION__);//displayString
	printf("%s\n",  __func__);    //displayString
	printf("%s\n",  __PRETTY_FUNCTION__);//displayString
}
```
# Inner function

Inner function (also known as **nested function**) allows defining a function inside a function.

C and CPP only support declaring a function inside a function, not defining it.

This available with both GCC and G++:

```c
#include <stdio.h>

void display_string(){
   void inner_function();
   printf("Hello, World !\n");//Hello, World !
   inner_function();
}

int main(){
   display_string();
}

void inner_function(){
   printf("Don't call any inner");
}
```
Inner function method is applied in [callback by function pointer](Callback%20function.md#handle-callback-by-function-pointer) where the [function pointer](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Pointer/Function%20pointer.md) is declared inside the callback function.
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

Multiple random numbers can be generated at the same time. This example will generate 3 random number less than 100:

```c
printf("Random number 1 %d\n", rand()%100);
printf("Random number 2 %d\n", rand()%100);
printf("Random number 3 %d\n", rand()%100);
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

void generate_random_number(float lower, float upper) {
	float number = (float)rand()/(float)(RAND_MAX) * (upper- lower) + lower;
	printf("%f", number);
}
  
int main() { 
    srand(time(0));
  
    generate_random_number(LOWER, UPPER);
  
    return 0;
}
```
