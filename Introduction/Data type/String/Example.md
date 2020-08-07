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