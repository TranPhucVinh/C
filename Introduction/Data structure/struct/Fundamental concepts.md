### Build a struct

Struct as data type and create an object from that struct

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

### Enter value for struct member

```cpp
#include <stdio.h>
#include <string.h>

struct databaseNode {
	int id;
	char stringValue[50];
} databaseNode0;

main(){
	printf("Enter ID: ");
	scanf("%d", &databaseNode0.id);
	getc(stdin); //To handle with issue scanf before fgets

	printf("Enter string value: ");
	fgets(databaseNode0.stringValue, 50, stdin); //fgets allow to enter value with space

	printf("databaseNode0 has id %d with string value %s \n", databaseNode0.id, databaseNode0.stringValue);
}	
```
