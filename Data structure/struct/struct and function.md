
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
