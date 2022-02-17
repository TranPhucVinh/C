## Introduction 

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

int result = defineFunction(6);
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

**Macro function side effect**

```c
#define SQUARE(x) (x*x)

printf("square(%d) = %d", 3, SQUARE(1+2));//5
```

Although we expect the result is ``9`` but the result is actually ``5 = 1 + 1*2* + 2``

Problem solve:

```c
#define SQUARE(x) ((x)*(x))
printf("square(%d) = %d", 3, SQUARE(1+2));//9
```

**Choosing between macro and function**

Macro create the inline code which will the shorten the execution time of the program, while the function takes longer time to execute.

If a macro is executed 20 times, then 20 lines of macro code will be added to the preprocessor which will expand the size of the compiled program (``.exe``, ``.dll``, ``.lib``,...)

If a function is called 20 times, only 1 copy of that function will be used inside the program, which will make the program size smaller than using the macro correspondingly.

It depends on execution times and program size requirement to choose between macro and function.

### Using macro to define

Check [Using macro to define](https://github.com/TranPhucVinh/C/blob/master/Introduction/Macro/Using%20macro%20to%20define.md)

## Stringizing operator (#)

The # operator turns the argument it precedes into a quoted string. 

```c
#define RETURN_STRING(displayedString) #displayedString

printf("%s\n", RETURN_STRING(Hello World !));//Hello World !
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

## Token-pasting operator (##)

The ``##`` pre-processing operator performs token pasting. When a macro is expanded, the two tokens on either side of each ``##`` operator are combined into a single token, which then replaces the ``##`` and the two original tokens in the macro expansion.

```c
#include <stdio.h>

#define number_cat(a,b) a##b
#define double_cat(a,b,c) a##b##c
#define string_cat(c,d) c##d

int main(){
   int xy = 10;
   char cd[] = "Hello";
   printf("%d\n", number_cat(x,y));//10
   printf("%d\n", number_cat(1,2));//12
   printf("%d\n", double_cat(1,2,3));//123
   printf("%s\n", string_cat(c,d));//Hello
   return 0;
}
```
