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

Find a first part and second part of a string splitted by a substring with ``strstr()``

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char displayed_string[] = "Hello, World !";
char *second_part = NULL;
char *first_part;

int main(int argc, char *argv[]){
    second_part = strstr(displayed_string, "or");
	if (second_part != NULL)	printf("%s\n", second_part);//orld !
	else printf("NULL\n");

	first_part = (char*) malloc((second_part - displayed_string) * sizeof(char));
	
    //Copy (second_part - displayed_string) character from displayed_string to first_part
    strncpy(first_part, displayed_string, second_part - displayed_string);
    printf("%s\n", first_part);//Hello, W
	free(first_part);
}
```

Split a string by substring

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
char *remove_substring(char *string, char *sub) {
    char *new_string = (char*) malloc(strlen(string) * sizeof(char));
    char *second_part = (char*) malloc( (strlen(string) - strlen(sub)) * sizeof(char));

    char *match;
    int len = strlen(sub);

    while ((match = strstr(string, sub))) {
        *match = '\0';
        strcat(second_part, match+len);
    }

    strcat(new_string, string);//string now has the value of the first part of char *string
    strcat(new_string, second_part);
    free(second_part);

    return new_string;
}
 
int main(int argc, const char *argv[]) {
    char test[] = "Hello, World!";
    char *new_string = remove_substring(test, "ll");
    printf("%s\n", new_string);
    free(new_string);
    return 0;
}
```

**Result**: ``Heo, World!``

### Replace substring inside a string

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char displayed_string[] = "String 1 underscore String 2";

char *replace_string_by_substring(char *original_string, char *substring, char *replace);

int main(){
    char *new_string = replace_string_by_substring(displayed_string, "underscore", "_");
    printf("%s\n", new_string);//String 1 _ String 2
    free(new_string);
}

char *replace_string_by_substring(char *orginal_string, char *substring, char *replace){
    char* match = strstr(orginal_string, substring);
    if(match)
    {
        int new_size = strlen(orginal_string) - strlen(substring) + strlen(replace) + 1;
        char* new_string = (char*) malloc(new_size);
        bzero(new_string, new_size);
        *match = '\0';
        strcat(new_string, orginal_string);
        strcat(new_string, replace);
        strcat(new_string, match + strlen(substring));
        return new_string;
    }
    else return NULL;
}
```

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
