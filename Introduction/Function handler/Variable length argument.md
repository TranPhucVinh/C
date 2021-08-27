Variable length argument is a feature that allows a function to receive any number of arguments. 

For **Variable length argument** to be used, an ``int`` variable is required to represent the total number variable arguments passed.

### va_arg()

```c
type va_arg(va_list ap, type)
```

* ``ap``:  object of type ``va_list``
* ``type``: type name

## Examples

### Example 1

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
### Example 2

Accessing the argument with ``stdarg.h``

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