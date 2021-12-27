### Example 1

**Example 1.0**: Delete garbage value of a string

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
### Example 2

Change value of a string by function using pointer

**Using strcpy()**

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

char displayedString[] = "Hello";

void changeString(char *stringParameter){
	strcpy(stringParameter, "Test");

	// stringParameter = "Test"; 
	// This won't work as the address of stringParameter is different from displayedString
}

int main(){
	printf("%s \n", displayedString); //Hello
	changeString(displayedString);
	printf("%s \n", displayedString); //Test
}
```
Change value a dynamic memory string:

This is a wrong implementation and results in a NULL string

```c
void formString(char *_displayedString);

int main () {
   	char *displayedString;
	formString(displayedString);
	printf("String: %s \n", displayedString);//NULLs
}   

void formString(char *_displayedString){
	_displayedString = (char *) malloc(15);
	strcpy(_displayedString, "Learn malloc");
	printf("formString: %s\n", _displayedString);//Learn malloc
}
```
**Problem solve**
```c		
#define bufferSize 100

char *displayedString;

void changeString(char *stringParameter){
	strcpy(stringParameter, "Test");
}

int main(){
	displayedString = (char*) malloc (bufferSize * sizeof(char));
	changeString(displayedString);
	printf("%s \n", displayedString);
}
```
**Using array index**
```c
char displayedString[] = "Hello";

void changeString(char *stringParameter){
  char otherString[] = "Change string";
  int index = 0;
  while(index < strlen(stringParameter)){
    stringParameter[index] =   otherString[index];
    index++;
  }
}

int main(){
	printf("%s \n", displayedString); //Hello
	changeString(displayedString);
	printf("%s \n", displayedString); //Chang
}
```

**Notice 1**: If declare

```c
char *displayedString = "Hello";
```

Then the ``changeString()`` function in 2 ways doesn't work and results in ``Segmentation fault (core dumped)``.

See also: ``Examples.md`` in ``AVR-Arduino-framework/Introduction/Data type/String/`` for the examples in Arduino framework.

**Notice 2**:

Passing the string to ``changeString()`` results in Segmentation fault

```c
void changeString(char *stringParameter){
	printf("%s \n", stringParameter);// Hello, World !
	strcpy(stringParameter, "Test");
	printf("%s \n", stringParameter);//Segmentation fault (core dumped)
}

int main(){
	changeString("Hello, World !");
}
```

See also: ``Examples.md`` in ``AVR-Arduino-framework/Introduction/Data type/String/`` for the examples in Arduino framework.

### Example 2

``strstr()``: Returns a pointer to the first occurrence of ``str2`` in ``str1``, or a null pointer if ``str2`` is not part of ``str1``.

**Return**: A pointer to the first occurrence in str1 of the entire sequence of characters specified in str2, or a null pointer if the sequence is not present in ``str1``.

Find a substring inside a string with ``strstr()``

```c
char displayedString[] = "Hello, World !";
char *leftString;

int main(int argc, char *argv[]){
    leftString = strstr(displayedString, "or");
	if (leftString != NULL)	printf("%s\n", leftString);
	else printf("NULL\n");
}
```

Split a string by substring

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
