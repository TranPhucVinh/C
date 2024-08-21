# Define a struct

Struct as a data type: **create an object** and a **struct array** from that struct

```c
#include <stdio.h>

struct StructObject {
	int id;
	char string_value[50];
};

int main(){
    struct StructObject obj_0 = {0, "Value 0"};//struct as type for varaible
	struct StructObject array[2];//struct as type for array
	struct StructObject obj_1 = {1, "Value 1"};
	struct StructObject obj_2 = {2, "Value 2"};
	array[0] = obj_1;
	array[1] = obj_2;
    printf("%d, %s\n", obj_0.id,obj_0.string_value);//0, Value 0
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
error: C99 designator ‘string_value’ outside aggregate initializer
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
# Enter value for struct member using scanf()

```cpp
#include <stdio.h>
#include <string.h>

struct StructObject {
	int id;
	char stringValue[50];
} struct_obj;

int main(){
	printf("Enter ID: ");
	scanf("%d", &struct_obj.id);
	getc(stdin); //To handle with issue scanf before fgets

	printf("Enter string value: ");
	fgets(struct_obj.stringValue, 50, stdin); //fgets allow to enter value with space

	printf("StructObject0 has id %d with string value %s \n", struct_obj.id, struct_obj.stringValue);
}		
```
# Address of a struct
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
# Flexible array member
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
    struct struct_data_type *struct_obj;

    struct_obj = (struct struct_data_type *) malloc(sizeof(int) + sizeof(char[strlen(str)]));
    struct_obj->id = 123;
    strcpy(struct_obj->str_value, str);
    printf("%d, %s\n", struct_obj->id, struct_obj->str_value);//0, Hello, World !

    // This is wrong as size of struct object is not declared for str_value
    // struct struct_data_type value_0 = {0, "Hello, World !"};//Wrong, compilation error
}
```
