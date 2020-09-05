### Delete a specific character from a string

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

### Split a string by sub string

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

### Remove the first character from a string

```c
#include <stdio.h>
#include <string.h>

char telegramReturn[] = ",\"chat\":{\"id\":-1001452272470,\"title\":\"TMA lab 6 SW\",\"type\":\"supergroup\"";

void firstCharRemove(char stringChar[500]);

int main(){
	firstCharRemove(telegramReturn);
	printf("%s", telegramReturn);
}

void firstCharRemove(char stringChar[500]){
    //remove character ","
	if (stringChar[0] == ',') memmove(stringChar, stringChar+1, strlen(stringChar));
}
```

### Split number and character from a string with strtol()

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
**Input** ``./a.out 123``

**Output**

```
The number (unsigned long integer) is 123
String part is:
ptr null
```