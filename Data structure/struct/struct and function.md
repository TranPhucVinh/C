# struct as a function argument

```c
#include <stdio.h>

struct StructObject {
	int id;
	char stringValue[50];
};

void structFunction(struct StructObject node);

int main(){
	struct StructObject node = {1, "String value"};
	structFunction(node);
}

void structFunction(struct StructObject node){
	printf("id is %d and string value is %s \n", node.id, node.stringValue);
}
```
# Function returns struct

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
# Function as member of a struct

Functions as struct members must be defined by using function pointer.

## Function without arguments

```c
#include <stdio.h>

void display_string(){
	printf("Hello, World !\n");
}

struct StructObject {
	int id;
	char string_value[50];
	void (*init)();
};

int main(){
    struct StructObject obj = {
		.id = 123,
		.string_value = "String value",
		.init = display_string
	};
	printf("%d %s\n", obj.id, obj.string_value);// 123 String value
	obj.init();// Hello, World !
}
```

## Function with arguments

```c
#include <stdio.h>

int add_two_number(int number1, int number2){
	return number1 + number2;
}

int subtract_two_number(int number1, int number2){
	return number1 - number2;
}

struct StructObject {
	int (*add_function_pointer)(int, int);
	int (*subtract_function_pointer)(int, int);
};

int main(){
	struct StructObject obj = {
		.add_function_pointer = add_two_number,
		.subtract_function_pointer = subtract_two_number
	};	

	printf("Add 2 numbers: %d\n", obj.add_function_pointer(30, 60));// 90
	printf("Subtract 2 numbers: %d\n", obj.subtract_function_pointer(30, 60));// -30
}
```

Functions can be set and called like this:

```c
struct StructObject obj;

obj.add_function_pointer = add_two_number;
obj.subtract_function_pointer = subtract_two_number;

printf("Add 2 numbers: %d\n", obj.add_function_pointer(30, 60));
printf("Subtract 2 numbers: %d\n", obj.subtract_function_pointer(30, 60));
```	

For struct pointer object:

```c
struct StructObject *obj;
obj = (struct StructObject *)malloc(sizeof(struct StructObject));

obj->add_function_pointer = add_two_number;
obj->subtract_function_pointer = subtract_two_number;	
```
