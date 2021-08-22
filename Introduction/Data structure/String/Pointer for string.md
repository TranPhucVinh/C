## Define

```c
char *displayedString = "displayedString";

printf("%s \n", displayedString); //Hello, World !
```
Or can define:
```c
char *displayedString;

int main(){ 
  displayedString = "Hello, World !";
  printf("%s \n", displayedString); //Hello, World !
}  
```

This program compiles normally with ``GCC``.

Compiling with ``G++`` gives warning:
```
warning: deprecated conversion from string constant to ‘char*’ [-Wwrite-strings]
```

```c
char *displayedString;
displayedString = "Hello, World !";

int main(){ 
  printf("%s \n", displayedString);
}  
```

Compile error with ``G++`` and ``GCC``:

**Error**:

```
error: conflicting types for ‘displayedString’
error: initializer element is not computable at load time
```

### Define a string pointer on heap memory

Check ``Dynamic memory allocation.md`` in ``Physical layer/Memory``: ``malloc()``.

### Other way to define

```c
#include <stdio.h>

#define HOST "example.com"
#define PORT "80"
#define PATH "/"

char *REQUEST = "GET " PATH " HTTP/1.0\r\n"
    "Host: "HOST":"PORT"\r\n"
    "User-Agent: esp-idf/1.0 esp32\r\n"
    "\r\n";

printf("string: %s", REQUEST);
```

### Error with strcpy()

```c
char *displayedString;
strcpy(displayedString,  "Hello, World !");
```
**Error**: ``Segmentation fault (core dumped)``

The same problem will happen to similar functions like ``sprintf()``, ``strncpy()`` and ``memmove()``

**Problem solved**: Check: ``Physical layer/Memory/Dynamic memory allocation.md``

### Index handler

```c
printf("ptrString[0]: %c \n", ptrString[0]); //ptrString[0]: H 
```

### Change value

```c
char *ptrString;
ptrString = "Hello, World !";
printf("%s \n", ptrString);  //Hello, World ! 

ptrString = "Change number";
printf("%s \n", ptrString);  //Change number
```

We cannot modify the string at later stage in program:

```c
char *ptrString;
ptrString = "Hello, World !";
ptrString[0] = 'a'; //Segmentation fault (core dumped)
```

See also: ``Char for string.md`` in ``AVR-Arduino-framework/Introduction/Data type/String/`` for the example of modifying a string by index in Arduino framework.

**Error**: Error when changing the string value with both ``strcat()`` and ``strncat()``.

```c
#include <stdio.h>
#include <string.h>

int main(){
  char *hw = "Hello, World!";
  char *returnChar = "ab";
  // strncat(hw, returnChar, 2);
  strcat(hw, returnChar);
  printf("%s\n", hw);
}
```
**Result**: ``Segmentation fault (core dumped)``

``strcat()`` and ``strncat()`` require ``hw`` to be the string char array to store the value while ``char *hw`` has fix address and memory size.

### Function returns a string

```c
char *returnString(){
  return "Hello, World !";
}

int main(){
	printf("%s ", returnString());
}
```

Using stack memory with ``static``:

```c
char *returnString(){
	static char string[14];
	strcpy(string, "Hello, World !");
	return string;
}
```
Using heap memory with ``malloc()``:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define stringSize 20

char *returnString();
int main(){
	char *returnedString;
	returnedString = returnString();
	printf("%s", returnedString);
}

char *returnString(){
	char *string;
	string = (char*) malloc(stringSize);
	strcpy(string, "Hello, World !");
	return string;
}
```