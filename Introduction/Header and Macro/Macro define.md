### Introduction 

````c
#define PRINT_HELLO_WORLD printf("Hello, World !")
#define a 		6
#define b    	(10)

printf("%d \n", a);//6
PRINT_HELLO_WORLD;//Hello, World !
printf("%d \n", b);//10
````

Using ``\`` to add a new line when define macro

```c
#define PI   \
3.14

printf("%lf", PI);
```
### Macro functions with arguments

```c
#define defineFunction(a) a+1

int  result = defineFunction(6);
printf("%d \n", result); //7
```

Argument can be passed to the marco function

```c
int a;
printf("%d \n", defineFunction(a=6)); //7
```

Perform multiples instruction inside a macro function

```c
#include <stdio.h>
#define defineFunction(a) a+1; printf("Line 1\n"); printf("Line 2\n")

int main(){
   int result = defineFunction(6);
   printf("%d", result);
}		
```

```
Line 1
Line 2
7
```

### Using macro to define

Define an int variable with a macro function

```c
#define DEFINE_INT_VARIABLE(id) int id

int main()
{  
 DEFINE_INT_VARIABLE(a);
 a = 29;
 printf("%d\n", a);//29
}
```

### Stringizing operator (#)

The # operator turns the argument it precedes into a quoted string. 

```c
#define RETURN_STRING(displayedString) #displayedString

char text[20];
strcpy(text, RETURN_STRING(Hello World !));
printf("%s\n", text);//Hello World !
```

``#`` doesn't support character ``,``:

```c
strcpy(text, RETURN_STRING(Hello, World !));//Error
```

Using ``#`` to define:

```c
#define RETURN_STRING(id) int id = #id

RETURN_STRING(HELLO_WORLD);
printf("%s\n", HELLO_WORLD);//HELLO_WORLD	
```

Definition with ``#`` doesn't support space and sensitive character like ``,``, ``;`` or ``!``.

### Redefine macro variable

With ``#define``

```c
#define integerValue 190

printf("%d \n", integerValue);//190
#undef integeValue
#define integerValue 100
printf("%d \n", integerValue);//100
```

With traditional variable definition

```c
int integerValue = 200;
printf("%d \n", integerValue); //200
#undef integeValue
#define integerValue 100
printf("%d \n", integerValue); //100
```

With just ``#undef integeValue``, the value still unchanges
```c
printf("%d \n", integerValue); //190
#undef integeValue
printf("%d \n", integerValue); //190
```

### Predefine 

Predefine during compilation using flag ``-D``

```c
#include <stdio.h>

//Variable name is not define
main(){
	printf("name: %d \n", name);
}	
```

Predefine during compilation: ``gcc -D name=12 test.c``

Result: ``name: 12``

Predefine with ``#ifndef``

```c
#include <stdio.h>

#ifndef name
#define name 4
#endif

main(){
	printf("name: %d \n", name);
}	
```

If compile ``gcc -D name=12 test.c``, then result is ``name: 12``