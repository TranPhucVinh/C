## Example 1

### struct as a function argument
```c
#include <stdio.h>

struct databaseNode {
	int id;
	char stringValue[50];
};

void structFunction(struct databaseNode node);

main(){
	struct databaseNode node = {1, "String value"};
	structFunction(node);
}

void structFunction(struct databaseNode node){
	printf("id is %d and string value is %s \n", node.id, node.stringValue);
}
```
### struct function

```c
#include <stdio.h>
#include <string.h>

struct databaseNode {
	int id;
	char stringValue[50];
};

struct databaseNode displayString();

main(){
    struct databaseNode returnNode = displayString();
    printf("returnNode.id: %d, returnNode.stringValue: %s", returnNode.id, returnNode.stringValue);
}

struct databaseNode displayString(){
    struct databaseNode node;
    node.id = 1;
    strcpy(node.stringValue, "Hello, World !");

    return node;
}
```

``struct`` a type with ``typedef``:

```c
#include <stdio.h>
#include <string.h>

struct databaseNode {
	int id;
	char stringValue[50];
};

typedef struct databaseNode Database;

Database displayString();

int main() {
	displayString();
}

Database displayString(){
    Database node;
    node.id = 1;
    strcpy(node.stringValue, "Hello, World !");
    printf("node.id %d, node.stringValue: %s\n", node.id, node.stringValue);
}
```
Define function of struct using function pointer:

```c
#include <stdio.h>

int add_two_number(int number1, int number2){
	return number1 + number2;
}

int subtract_two_number(int number1, int number2){
	return number1 - number2;
}

struct databaseNode {
	int (*add_function_pointer)(int, int);
	int (*subtract_function_pointer)(int, int);
};

int main(){
	struct databaseNode databaseNode0 = {
		.add_function_pointer = add_two_number,
		.subtract_function_pointer = subtract_two_number
	};	

	printf("Add 2 numbers: %d\n", databaseNode0.add_function_pointer(30, 60));
	printf("Subtract 2 numbers: %d\n", databaseNode0.subtract_function_pointer(12, 120));
}
```
## Example 2

Nested struct

```c
struct linkedDatabaseNode{
    int id;
    char stringValue[50];
};

struct databaseNode  
{
   int id;
   struct linkedDatabaseNode nextNode;
};

int main()
{
    struct databaseNode databaseNode0 = {1, 2, "Displayed string"};
    printf("Member databaseNode0 has id %d\n", databaseNode0.id); 

    printf("ID of databaseNode0 from linkedDatabaseNode is %d, and the displayed string: %s", databaseNode0.nextNode.id, databaseNode0.nextNode.stringValue);
}
```

**Output**

```
Member databaseNode0 has id 1
ID of databaseNode0 from linkedDatabaseNode is 2, and the displayed string: Displayed string
```
### Example 3

Split a string with the following sequence ``host`` and ``port``

```c
#include <stdio.h>

char host[19];
char port[3];

void struct_data_parsing(char *data);

int main() {
	char displayed[] = "demo.thingsboard.io443";
	struct_data_parsing(displayed);
} 

void struct_data_parsing(char *data){
    struct struct_data {
        char host[19];
        char port[3];
    } data_frame;

    memcpy(&data_frame, data, strlen(data));
    strcpy(host, data_frame.host);
    strcpy(port, data_frame.port);
}
```

(View the result by ``gdb``)

### Example 4

Parsing a char array into the following fields

Char array: ``0x24 0x00 0x01 0x1A 0x05 0x1F 0x20 0x2F 0x1C 0x17 0x20 0x61``

* DCD header: ``$`` (``0x24``)
* ID: ``0001`` (``0x00`` ``0x01``)
* Environment humidity: ``26,05`` (``0x1A`` ``0x05``)
* Environment temperature: ``31,32``(``0x1F`` ``0x20``)
* Soil humidity: ``47,28`` (``0x2F`` ``0x1C``)
* Soil temperature: ``23,32`` (``0x17`` ``0x20``)
* Checksum: 0x61 (OR 11 bytes give 0x0261, 0x61 is the lower byte)

**Program**: ``struct_data_parsing.c``