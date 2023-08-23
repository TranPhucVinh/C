# Build a struct

Struct as a data type and create an object from that struct

```c
#include <stdio.h>

struct struct_data_type {
	int id;
	char string_value[50];
};

int main(){
    struct struct_data_type value_0 = {0, "Value 0"};//struct as type for varaible
	struct struct_data_type array[2];//struct as type for array
	struct struct_data_type value_1 = {1, "Value 1"};
	struct struct_data_type value_2 = {2, "Value 2"};
	array[0] = value_1;
	array[1] = value_2;
    printf("%d, %s\n", value_0.id,value_0.string_value);//0, Value 0
	printf("%d, %s\n", array[0].id, array[0].string_value);//1, Value 1
}
```

Can define an object value like this way:
```c
struct struct_data_type value_0 = {
	.id = 0,
	.string_value = "Value 0"
};
```
This compile normally on GCC but gives error in G++:

```
error: C99 designator ‘stringValue’ outside aggregate initializer
};
```
Or by this way:

```c
struct databaseNode {
	int id;
	char stringValue[50];
} databaseNode0;

strcpy(databaseNode0.stringValue, "Name"); //to set variable with char in struct
databaseNode0.id = 2;
printf("Member databaseNode0 has id %d with string value %s \n", databaseNode0.id, databaseNode0.stringValue);
```
**Output**
```
Member databaseNode0 has id 2 with string value Name 
```

## Address of a struct

```c
struct student{
		int id;
		char name[50];
		char classroom[50];
};

int main() {
	struct student student_object = { 1977, " student_object", "Free Lancer" };

	printf("value &student_object: %p \n", &student_object); //0x7ffe09debe80
	printf("value &student_object.id: %p \n", &student_object.id); //0x7ffe09debe80
	printf("value &student_object.name: %p \n", &student_object.name); //0x7ffe09debe84
	printf("value &student_object.classroom: %p \n", &student_object.classroom); //0x7ffe09debeb6
}
```

Address of ``student_object`` and ``student_object.id`` are the same.
## Flexible array member
struct allows declaring an array as its member without the initial size, which is called **flexible array member**. struct object with that flexible array member then must be a pointer as it needs to initialize the size. 

**Flexible array member** of a struct must be the last member of that struct
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct struct_data_type {
	int id;

    // Flexible Array Member array must be the last member of a struct
	char str_value[];
};

char str[] = "Hello, World !";
int main(){
    struct struct_data_type *val;

    val = (struct struct_data_type *) malloc(sizeof(int) + sizeof(char[strlen(str)]));
    val->id = 123;
    strcpy(val->str_value, str);
    printf("%d, %s\n", val->id, val->str_value);//0, Hello, World !

    // This is wrong as size of struct object is not declared for str_value
    // struct struct_data_type value_0 = {0, "Hello, World !"};//Wrong, compilation error
}
```
# struct as data type of function

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

# struct as a function argument

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

# Function as member of a struct

Functions as struct members must be defined by using function pointer.

## Function without arguments

```c
#include <stdio.h>

void display_string(){
	printf("Hello, World !\n");
}

struct struct_data_type {
	int id;
	char string_value[50];
	void (*init)();
};

int main(){
    struct struct_data_type value_0 = {
		.id = 123,
		.string_value = "String value",
		.init = display_string
	};
	printf("%d %s\n", value_0.id, value_0.string_value);
	value_0.init();
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

Functions can be set and called like this:

```c
struct databaseNode databaseNode0;

databaseNode0.add_function_pointer = add_two_number;
databaseNode0.subtract_function_pointer = subtract_two_number;

printf("Add 2 numbers: %d\n", databaseNode0.add_function_pointer(30, 60));
printf("Subtract 2 numbers: %d\n", databaseNode0.subtract_function_pointer(12, 120));
```	

For struct pointer object:

```c
struct databaseNode *databaseNode0;
databaseNode0 = (struct databaseNode *)malloc(sizeof(struct databaseNode));

databaseNode0->add_function_pointer = add_two_number;
databaseNode0->subtract_function_pointer = subtract_two_number;
```
