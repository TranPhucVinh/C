# Change value of a string by function using pointer

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

# Parse an IP address string

Parsing an IP address string: [parsing_ip_address_string.cpp](parsing_ip_address_string.cpp)

# Reverse a string

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
# Split a string into specific sequences
Split a string into the following sequence: ``host`` and ``port``

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STDOUT_FD 1

char displayed[] = "demo.thingsboard.io443";
char host[19], port[3];

int main() {
    char *ptr;
    ptr = (char*) malloc(19 * sizeof(char));

    // ptr = reinterpret_cast<char*>(displayed);
    ptr = displayed;

    strcpy(host, ptr);

    write(STDOUT_FD, host, 19);
    write(STDOUT_FD, "\n", 2);

    // Must not use printf() here to display the string as it will print out
    // wrong string, like demo.thingsboard.io443

    ptr += 19;
    strcpy(port, ptr);
    write(STDOUT_FD, port, 3);
    write(STDOUT_FD, "\n", 2);
}
```
[struct](../struct) can also be used to [implement this](../struct/Examples/Use%20struct%20for%20string%20parsing.md#parsing-a-hex-char-array)
