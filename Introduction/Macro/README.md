## Introduction 

````c
#define a 		6
#define b    	(10)
#define RETURN_INT() 		10
#define PRINT_HELLO_WORLD printf("Hello, World !")

printf("%d \n", a);//6
printf("%d \n", b);//10
PRINT_HELLO_WORLD;//Hello, World !
printf("%d \n", RETURN_INT());//10
````

Using ``\`` to add a new line when define macro

```c
#define PI   \
3.14

printf("%lf", PI);
```
**Can't use return in macro function**:

```c
#define RETURN_INT() return 10 //This is wrong and must not be done
```

Error:

```
test.c:6:24: error: expected primary-expression before ‘return’
 #define RETURN_INT()   return 10;
```

**Can't get address of macros by &**

Macros are never allocated a memory. Before the code is compiled, the compiler does a text search in the file and replace all Macros with their value.

## Macro function

For implementation of macro function, check [macro function document](Macro%20function.md).

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
**Error**

```c
#define number_cat(a,b) a##b

printf("%d\n", number_cat(number_cat(1,2), 2));//Error
```

This will give error:

```
test.c:6:44: error: pasting ")" and "2" does not give a valid preprocessing token
    printf("%d\n", number_cat(number_cat(1,2), 2));
test.c:6:44: error: ‘number_cat’ was not declared in this scope
    printf("%d\n", number_cat(number_cat(1,2), 2));
                                            ^
```

That happen as ``number_cat(number_cat(1,2), 2) = 1##2##2``. ``1##2##2`` is not defined.
