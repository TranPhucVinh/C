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
**Can't get address of macros by &**

Macros are never allocated a memory. Before the code is compiled, the compiler does a text search in the file and replace all Macros with their value.

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
**Choosing between macro and function**

Macro create the inline code which will the shorten the execution time of the program, while the function takes longer time to execute.

If a macro is executed 20 times, then 20 lines of macro code will be added to the preprocessor which will expand the size of the compiled program (``.exe``, ``.dll``, ``.lib``,...)

If a function is called 20 times, only 1 copy of that function will be used inside the program, which will make the program size smaller than using the macro correspondingly.

It depends on execution times and program size requirement to choose between macro and function.

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

### The difference between #if defined() and #ifdef()

The difference between the two is that ``#ifdef`` can only use a single condition, while ``#if defined(NAME)`` can do compound conditionals.

```c
#if defined(WIN32) && !defined(UNIX)
/* Do windows stuff */
#elif defined(UNIX) && !defined(WIN32)
/* Do linux stuff */
#else
/* Error, both can't be defined or undefined same time */
#endif
```

### Stringizing operator (#)

The # operator turns the argument it precedes into a quoted string. 

```c
#define RETURN_STRING(displayedString) #displayedString

char text[20];
strcpy(text, RETURN_STRING(Hello World !));
printf("%s\n", text);//Hello World !
```

Definition with ``#`` doesn't support space and sensitive character like ``,``, ``;`` or ``!``.

```c
strcpy(text, RETURN_STRING(Hello, World !));//Error
```

Using ``#`` to define string char variable:

```c
#define RETURN_STRING(id) const char *id = #id

RETURN_STRING(string_variable);
printf("%s\n", string_variable);//string_variable	
```
As ``#`` related to string variable, declare with other data type will give warning or error

```c
#define RETURN_STRING(id) int id = #id

RETURN_STRING(HELLO_WORLD);
printf("%s\n", HELLO_WORLD);//HELLO_WORLD	
```

**Error**: 

```
error: invalid conversion from ‘const char*’ to ‘int’ [-fpermissive]
```

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