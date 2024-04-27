**Variable length argument** is a feature that allows a function to receive any number of arguments. Function that supports variable length argument is called **variadic function**. Examples of **variadic functions** are ``printf()``, ``sprintf()``,...

For **variable length argument** to be used, an ``int`` variable is required to represent the total number variable arguments passed.
# API
## va_arg()

```c
type va_arg(va_list ap, type)
```

* ``ap``:  object of type ``va_list``
* ``type``: type name
# va_copy()
```c
void va_copy(va_list dest, va_list src);
```
Copy **variable length argument** ``src`` to ``dest``
# Define a variadic function

```c
#include <stdio.h>

int multipleArgumentsFunction(char *displayedString1, char *displayedString2,...){
	printf("%s\n", displayedString1);
	printf("%s\n", displayedString2);
}

int main() {
	multipleArgumentsFunction("String 1", "String 2", "String 3", 1, 2, 3);
}   
```
```
String 1
String 2
```
# Accessing all variable length arguments

## Accessing the argument with stdarg.h

```c
#include <stdio.h>
#include <stdarg.h> //for va_list, va_start(), va_end()

int multipleArgumentsFunction(int totalArgument,...){
	va_list valist;
	va_start(valist, totalArgument);

	printf("%s\n", va_arg(valist, char*));
	printf("%s\n", va_arg(valist, char*));
	printf("%s\n", va_arg(valist, char*));
	va_end(valist); //clean up the memory assigned to va_list variable.
	return 0;
}

int main() {
	multipleArgumentsFunction(3, "String 1", "String 2", "String 3");
}  
```

``int totalArgument`` can goes behind other argument inside the function

```c
#include <stdio.h>
#include <stdarg.h> //for va_list, va_start(), va_end()

int multipleArgumentsFunction(const char *displayedString, int totalArgument,...){
	printf("%s\n", displayedString);

	va_list valist;
	va_start(valist, totalArgument);

	printf("%s\n", va_arg(valist, char*));
	printf("%s\n", va_arg(valist, char*));
	va_end(valist); //clean up the memory assigned to va_list variable.
	return 0;
}

int main() {
	multipleArgumentsFunction("Hello, World !", 2, "String 1", "String 2");
} 
```
```
Hello, World !
String 1
String 2
```

``int totalArgument`` can be outside function ``multipleArgumentsFunction()``

```c
#include <stdio.h>
#include <stdarg.h> //for va_list, va_start(), va_end()

int totalArgument = 3;

int multipleArgumentsFunction(char *displayedString,...){
	va_list valist;
	va_start(valist, totalArgument);

	printf("%s\n", displayedString);//String 1
	printf("%s\n", va_arg(valist, char*));//String 2
	printf("%s\n", va_arg(valist, char*));//String 3
	printf("%s\n", va_arg(valist, char*));//String 4
	va_end(valist); //clean up the memory assigned to va_list variable.
	return 0;
}

int main() {
	multipleArgumentsFunction("String 1", "String 2", "String 3", "String 4");
} 
```

**Note**: This function gives warning in both G++ and GCC

```
test.c:48:2: warning: second parameter of ‘va_start’ not last named argument [-Wvarargs]
  va_start(valist, totalArgument);
  ^
```

## Change value of a string as a variable length argument
**By using the same argument**
```c
#include <stdio.h>
#include <string.h>
#include <stdarg.h> //for va_list, va_start(), va_end()

int multipleArgumentsFunction(int totalArgument,...){
	va_list valist;
	va_start(valist, totalArgument);

	strcpy(va_arg(valist, char*), "Display string");
	va_end(valist); //clean up the memory assigned to va_list variable.
	return 0;
}

int main() {
	char displayedString[] = "Hello, World !";
	printf("%s\n", displayedString);//Hello, World !
	multipleArgumentsFunction(1, displayedString);
	printf("%s\n", displayedString);//Display string
} 
```
**By using [va_copy()](#va_copy)**
```c
#include <stdio.h>
#include <string.h>
#include <stdarg.h> //for va_list, va_start(), va_end()

int multipleArgumentsFunction(int totalArgument,...){
    va_list src;        
    va_list dest;            

    va_start(src, totalArgument);                   
    strcpy(va_arg(src, char*), "Display string");
    va_copy(dest, src);
	va_end(dest);
	return 0;
}

int main() {
	char displayedString[] = "Hello, World !";
	printf("%s\n", displayedString);//Hello, World !
	multipleArgumentsFunction(1, displayedString);
	printf("%s\n", displayedString);//Display string
} 
```
## Add sum and min of a sequence
```c
int sum(int totalArgument,...){
    int _sum = 0;
	va_list valist;
	va_start(valist, totalArgument);

    for (int i = 0; i < totalArgument; i++){
        _sum += va_arg(valist, int);
    }
	return _sum;
}

int min(int totalArgument,...){
    va_list valist;
    va_start(valist, totalArgument);

    int min = va_arg(valist, int);
    
    for (int i = 1; i < totalArgument; i++){
        int val = va_arg(valist, int);
        if (val <= min) min = val;
    }
    return min;
}

int main() {
	printf("%d", sum(5, 1, 2, 3, 4, 5));
	printf("%d", min(5, 1, -19, 3, 4, 5));
}  
```
