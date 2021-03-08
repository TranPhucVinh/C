## Using char*

```c
char *displayedString;

int main(){ 
  displayedString = "Hello, World !";
  printf("%s \n", displayedString); //Hello, World !
}  
```

Compile with ``G++`` gives warning:
```
warning: deprecated conversion from string constant to ‘char*’ [-Wwrite-strings]
```

Compile error with ``G++`` and ``GCC``:

```c
char *displayedString;
displayedString = "Hello, World !";

int main(){ 
  printf("%s \n", displayedString);
}  
```

**Error**:

```
error: conflicting types for ‘displayedString’
error: initializer element is not computable at load time
```

Index handler:

```c
printf("ptrString[0]: %c \n", ptrString[0]); //ptrString[0]: H 
```

### Change value

```c
char *ptrString;
ptrString = "Hello, World !";
printf("%s \n", ptrString); 

ptrString = "Change number";
printf("%s \n", ptrString); 
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

## Using char[]

```c
char hw[] = "Hello, World!";
printf("%s \n", hw); //Hello, World! 
```

Index handler

```c
char helloWorld[] = "Hello world 10 times";
printf("%s \n",helloWorld+3); //lo world 10 times
printf("%c \n", helloWorld[3]); //l
```

Change value

```c
char hw[] = "Hello, World!";
printf("%s \n", hw); //Hello, World! 
hw[0] = 'a';
printf("%s \n", hw); //aello, World! 
```

Get address of pointer char

```c
printf("returnChar: %p \n", returnChar); //Address of returnChar is : 0x62FE30
```

### String as argument in function

```c
void printString(char hw[]){
	printf("%s ", hw);
}

void printStringPointer(char *hw){
	printf("%s ", hw);
}

int main(){
	char str1[] = "Hello, World \n";
	printString(str1); //Hello, World
	printStringPointer(str1); //Hello, World
}
```

## Size of a string char

``size_t strlen(const char *)``: Return length of a string

``sizeof()``: For ``sizeof()`` and way to get size of a ``char*`` string, check  ``sizeof()`` in ``Physical layer/Memory/Pointer/Introduction.md``

**Example**
```c
char string1[20];
printf("%d\n", strlen(string1)); //3
printf("%d\n", sizeof(string1)); //20
char string2[] = "Hello, World !";//14 characters
printf("%d\n", strlen(string2)); //14
printf("%d\n", sizeof(string2)); //15
char *string3;
printf("%d\n", sizeof(string3));//8
char *string4 = "Hello, World !";
printf("%d\n", strlen(string4));//14
printf("%d\n", sizeof(string4));//8
```

This will result in core dumped error:
```c
char *string3;
printf("%d\n", strlen(string3));//Segmentation fault (core dumped)
```

### Overflow string char buffer

```c
char displayedString[1];
strcpy(displayedString,"Hello, World!!");
```

**Error**:

```
*** stack smashing detected ***: ./a.out terminated
Aborted (core dumped)
```

To fix overflow issue, using Heap memory with malloc. Check: ``Physical layer/Memory/Dynamic memory allocation.md``
