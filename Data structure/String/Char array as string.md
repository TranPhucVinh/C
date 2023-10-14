# Define

```c
char hw[] = "Hello, World!";
printf("%s \n", hw); //Hello, World! 
unsigned char displayedString[] = "Hello, World !";
printf("%s\n", displayedString);////Hello, World!
```

**Define with multiple ""**

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

This define can be implemented identically  with [char pointer](Char%20pointer%20as%20string.md)

[Define with formatted string, this is useful when using snprintf() function](https://github.com/TranPhucVinh/C/blob/master/Data%20structure/String/String%20copy%20functions.md#snprintf)
```c
char displayed_string[] = "String: %s ";
char buffer[50];

snprintf(buffer, 50, displayed_string, "Hello, World !");
printf("%s", buffer);//String: Hello, World ! 
```
# Read by index

```c
char helloWorld[] = "Hello world 10 times";
printf("%s \n",helloWorld+3); //lo world 10 times
printf("%c \n", helloWorld[3]); //l
```

# Change string value at specific index

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

# Get size of string char

Use ``sizeof()`` function:

**Example**
```c
char string1[20];
printf("%d\n", sizeof(string1)); //20
char string2[] = "Hello, World !";//14 characters
printf("%d\n", sizeof(string2)); //15
```

# Char array as argument in function

For char array as function argument, its size must be gotten by ``strlen()``, not ``sizeof()``

```c
void printString(char hw[]){
	printf("%s\n", hw);
    printf("String size: %d\n", strlen(hw));//14
	printf("Can't get char array argument by sizeof(), %d\n", sizeof(hw));//8
}

int main(){
	char str1[] = "Hello, World !";
	printString(str1); //Hello, World
}
```

# Overflow a char buffer as string

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

To fix overflow issue, using [heap memory with malloc() for string](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Dynamic%20memory%20allocation/Using%20stdlib.md#malloc-for-string)
