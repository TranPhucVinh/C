## Using char*

```c
char *ptrString;

int main(){ 
  ptrString = "Hello, World !";
  printf("%s \n", ptrString); //Hello, World !
}  
```

Compile with ``G++`` gives warning:
```
warning: deprecated conversion from string constant to ‘char*’ [-Wwrite-strings]
```

Compile error with ``G++`` and ``GCC``:

```c
char *ptrString;
ptrString = "Hello, World !";

int main(){ 
  printf("%s \n", ptrString); //Hello, World !
}  
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

### sizeof()

For ``sizeof()`` and way to get size of a ``char*`` string, check  ``sizeof()`` in ``Physical layer/Memory/Pointer/Introduction.md``

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

### strlen()

``size_t strlen(const char *)``: Return length of a string

```c
char stringSize[] = "Hello, World!";
char *pointerString = "Pointer string";

//%ld for size_t as long unsignee int
printf("%ld", strlen(stringSize)); //13
printf("%ld", strlen(pointerString)); //14
```

### Overflow string char buffer

```c
char displayString[1];
strcpy(displayString,"Hello, World!!");
```

**Error**:

```
*** stack smashing detected ***: ./a.out terminated
Aborted (core dumped)
```

To fix overflow issue, using Heap memory with malloc. Check: ``Physical layer/Memory/Dynamic memory allocation.md``
