# Remove garbage value of a string

Using ``memset()``

```c
char displayedString[30];
printf("%s\n", displayedString); //Print garbage value
memset(displayedString, 0, sizeof(displayedString));
printf("%s\n", displayedString); //Print NULl string
```
Using ``bzero()``

```c
char displayedString[30];
printf("%s\n", displayedString); //Print garbage value
bzero(displayedString, sizeof(displayedString));
printf("%s\n", displayedString); //Print NULl string
```

# Remove a specific character from a string

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

## Remove the first character from a string

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

# Remove a character from a string with specified index 

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

char modifiedString[] = "Hello, World !";

void splitStringByIndex(int index, char* string);

int main(){
	splitStringByIndex(1, modifiedString);//Hllo, World !
	splitStringByIndex(1, modifiedString);//Hlo, World !
	splitStringByIndex(1, modifiedString);//Hlo, World !
}

void splitStringByIndex(int index, char* string){
	int i = index;

	while(i <= strlen(string)){
		string[i] = string[i+1];
		i++;
	}
	printf("%s\n", string);
}
```

To avoid changing the same string every time calling the function:

```c
void splitStringByIndex(int index, char* string){
	char newString[100]; //Can't declare: char *newString for later strcpy() function
	strcpy(newString, string);

	int i = index;

	while(i <= strlen(newString)){
		newString[i] = newString[i+1];
		i++;
	}
	printf("%s\n", newString);
}
```

**Notice 1**: 

Calling ``splitStringByIndex(1, "Hello, World !")`` results in ``Segmentation fault (core dumped)``

See also: ``Examples.md`` in ``AVR-Arduino-framework/Introduction/Data type/String/`` for passing a pure string to function ``splitStringByIndex()`` in Arduino framework.

**Notice 2**

If declare:

```c
char* modifiedString = "Hello, World !";

splitStringByIndex(1, modifiedString);
```

This will result in ``Segmentation fault (core dumped)``.

See also: ``Examples.md`` in ``AVR-Arduino-framework/Introduction/Data type/String/`` for declaring with a string pointer in Arduino framework.

## Index specified by executed argument

* argv[1]: Index to remove character
* argv[2]: String to process

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void splitStringByIndex(int index, char* string);

char *dummyString, *enteredString;
int enteredIndex; 

int main(int argc, char *argv[]) {
    if (argc == 3){
		enteredString = argv[2];
		enteredIndex = strtol(argv[1], &dummyString, 10);
		if (!strcmp(dummyString, "")){
			if (enteredIndex < 0) {
				printf("Negative index value is invalid\n");
				return 0;
			}
			if (enteredIndex > strlen(enteredString)){
				printf("Index is bigger than string size\n");
				return 0;
			}

			printf("String before delete: %s\n", enteredString);
			splitStringByIndex(enteredIndex, enteredString);
			printf("String after delete: %s\n", enteredString);
        } else {
			printf("You have entered invalid index value");
		}
    } else if (argc > 3) puts("Just only one argument is excepted");
    else puts("You haven't entered enough parameter");   
    return(0);
}

void splitStringByIndex(int index, char* string){
	//Avoid changing the same string every time calling the function
	char newString[100]; //Can't use char *newString
	strcpy(newString, string);

	int i = index;

	while(i <= strlen(newString)){
		newString[i] = newString[i+1];
		i++;
	}

	int i = index;

	while(i <= strlen(string)){
		string[i] = string[i+1];
		i++;
	}
}
```
