**Example 1.0**: Delete garbage value of a string

```c
char displayedString[30];
printf("%s\n", displayedString); //Print garbage value
memset(displayedString, 0, strlen(displayedString));
printf("%s\n", displayedString); //Print NULl string
```

**Example 1.1**: Delete a specific character from a string

```cpp
#include <stdio.h>

void removeCharFromString(char *stringChar, char c){
    if (NULL == stringChar) return;

    char *parsedString = stringChar;

    while (*stringChar){
        if (*stringChar != c){
            *parsedString++ = *stringChar;
        }
        stringChar++;
    }
    *parsedString = '\0';
}

main() {
    char stringToRemove[] = "Hello, World";
    printf("Before parse: %s \n", stringToRemove);
	removeCharFromString(stringToRemove, 'l');
    printf("After parse: %s \n", stringToRemove);
}
```
**Result**

```
Before parse: Hello, World 
After parse: Heo, Word 
```
**Example 1.2**: Change value of a string by function using pointer

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t str[] = "Hello";

void printString(uint8_t *hw){
	strcpy(hw, "Test");

	// hw = "Test"; 
	// This won't work as the address of hw is different from str
}

int main(){
	printf("%s \n", str);
	printString(str);
	printf("%s \n", str);
}
```
Other way by using array index
```c
char displayedString[] = "Hello";

void printString(char *changedString){
  char otherString[] = "Change string";
  int index = 0;
  while(index < strlen(changedString)){
    changedString[index] =   otherString[index];
    index++;
  }
}

int main(){
	printf("%s \n", displayedString); //Hello
	printString(displayedString);
	printf("%s \n", displayedString); //Chang
}
```

**Example 2**: Split a string by sub string

```cpp
#include <stdio.h>
#include <string.h>
 
void removeSubString (char *string, char *sub) {
    char *match;
    int len = strlen(sub);
    while ((match = strstr(string, sub))) {
        *match = '\0';
        strcat(string, match+len);
    }
}
 
int main(int argc, const char *argv[]) {
    char test[] = "Hello, World!";
    removeSubString(test, "ll");
    puts(test);
    return 0;
}
```

**Result**: ``Heo, World!``

**Example 3**: Split number and character from a string with ``strtol()``

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[] = "12Hello";
    char *ptr;
    long ret;

    ret = strtol(str, &ptr, 10);
    printf("The number (unsigned long integer) is %ld\n", ret);
    printf("String part is: %s\n", ptr);
    if (!strlen(ptr)) puts("ptr null");
    return(0);
}
```
**Output**

```
The number (unsigned long integer) is 12
String part is:Hello
```

Split the entered string from executed argument

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *ptr;
    long ret;

    if (argc > 1){
        ret = strtol(argv[1], &ptr, 10);
        printf("The number (unsigned long integer) is %ld\n", ret);
        printf("String part is:%s\n", ptr);
        if (!strlen(ptr)) puts("No string found in argument");
    } else puts("You haven't entered anything");   
    return(0);
}
```
**Input** ``./a.out 123abc``

**Output**

```
The number (unsigned long integer) is 123
String part is: abc
ptr null
```

**Input** ``./a.out 123``

**Output**

```
The number (unsigned long integer) is 123
String part is:
ptr null
```
