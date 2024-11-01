# Introduction 

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
## Macro to get OS type
```c
#include <stdio.h>

int main()
{
    #ifdef __linux__ 
        printf("Linux\n");
    #elif _WIN64
        printf("Windows 64\n");
    #endif
}
```

**Can't get address of macros by &**

Macros are never allocated a memory. Before the code is compiled, the compiler does a text search in the file and replace all Macros with their value.

# Define variables by macro

## Define normal variable with macro

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

## Define pointer variable with macro

```c
#include <stdio.h>

#define define_pointer(a) int *pointer = &a

int main()
{  
	int a = 123;
	define_pointer(a);
	printf("%d\n", *pointer);//123
}
```

# Macro defines a block of operation

**Use a variable inside macro before it is defined**

```c
#include <stdio.h>

#define CONDITION_CHECK {\
    if (a == 4) printf("a == 4\n");\
    else printf("a != 4\n");\
}

int main(){
    int a;
    a = 4;
    CONDITION_CHECK;//a==4
    a = 10;
    CONDITION_CHECK;//a !=4
}
```

**Use return inside macro block of operations**

```c
#include <stdio.h>

#define RET_MARCO return 4

int function(){
    RET_MARCO;
}

int main(){
    printf("%d\n", function());
    printf("Then quit main() function by RET_MARCO\n");
    RET_MARCO;//main() will quit here
    printf("This line won't print out after calling macro RET_MARCO\n");
}
```

# Macro function

For implementation of macro function, check [macro function document](Macro%20function.md).

# Condition in macro

For conditional check like ``#ifdef``, ``#undef``,... check [Condition in macro document](Condition%20in%20macro.md)

# Stringizing operator (#)

The ``#`` operator turns the argument it precedes into a quoted string. 

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
