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

As the issue of **pass by value**, passing a struct by value to a function to change its member value won't give effect:

```c
#include <stdio.h>

struct databaseNode {
	int id;
	char stringValue[50];
};

void change_value(struct databaseNode node);

main(){
	struct databaseNode node = {1, "String value"};
   printf("before: id is %d and string value is %s \n", node.id, node.stringValue);//before: id is 1 and string value is String value
	change_value(node);
   printf("after: id is %d and string value is %s \n", node.id, node.stringValue);//after: id is 1 and string value is String value 
}

void change_value(struct databaseNode node){
	node.id = 100;
   strcpy(node.stringValue, "Change string");
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