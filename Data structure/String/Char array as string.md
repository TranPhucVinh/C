### Define

```c
char hw[] = "Hello, World!";
printf("%s \n", hw); //Hello, World! 
unsigned char displayedString[] = "Hello, World !";
printf("%s\n", displayedString);////Hello, World!
```

**Other way to define**

```c
#include <stdio.h>

#define HOST "example.com"
#define PORT "80"
#define PATH "/"

char REQUEST[] = "GET " PATH " HTTP/1.0\r\n"
    "Host: "HOST":"PORT"\r\n"
    "User-Agent: esp-idf/1.0 esp32\r\n"
    "\r\n";

printf("string: %s", REQUEST);
```

This define can identically implemented with [char pointer](https://github.com/TranPhucVinh/C/edit/master/Introduction/Data%20structure/String/Char%20pointer%20as%20string.md)

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

## Get size of string char

Use ``sizeof()`` function:

**Example**
```c
char string1[20];
printf("%d\n", sizeof(string1)); //20
char string2[] = "Hello, World !";//14 characters
printf("%d\n", sizeof(string2)); //15
```

### Overflow string char buffer

Error **Stack smashing detected** happens due to buffer overflow

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