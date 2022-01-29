## Example 1

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

## Example 2

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

## Example 3

Parsing for IP address

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseBytes(const char* stringParameter, char sep, unsigned long* stringResult, int maxBytes, int base);

int main(){
	char ipString[] = "192.168.255.255";
    /*
		ip array must be unsigned long for being converted by strtoul. If set as char ip[4], the result will be signed number as char by default is signed number
	*/	
	unsigned long ip[4];

	parseBytes(ipString, '.', ip, 4, 10);

	printf("ip[1]: %d\n", ip[0]);
	printf("ip[2]: %d\n", ip[1]);
	printf("ip[3]: %d\n", ip[2]);
	printf("ip[4]: %d\n", ip[3]);
}

void parseBytes(const char* stringParameter, char sep, unsigned long* stringResult, int maxBytes, int base) {
    for (int i = 0; i < maxBytes; i++) {
        stringResult[i] = strtoul(stringParameter, NULL, base);  // Convert byte: strtoul: string to unsigned long
        stringParameter = strchr(stringParameter, sep);               // Find next separator
        if (stringParameter == NULL || *stringParameter == '\0') {
            break;                            // No more separators, exit
        }
        stringParameter++;                                // Point to next character after separator
    }
}
```
## Example 4

Reverse a string

```c
#include <stdio.h>
#include <stdlib.h>

char displayed_string[] = "Hello, World !";

int main(){
	size_t string_size = sizeof(displayed_string);
	printf("size: %d\n", string_size);
	char *new_string;
	new_string = (char*) malloc(string_size * sizeof(char));

	for (int i = 0; i < string_size; i++)
    {
        new_string[i] = displayed_string[string_size - 2 - i];
    }
	new_string[string_size] = NULL;
	printf("New string: %s\n", new_string);
}
```