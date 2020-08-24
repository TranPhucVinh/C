### Introduction

```c
#include <stdio.h>

struct databaseNode {
	int id;
	char stringValue[50];
};

main(){
	struct databaseNode databaseNode0 = {1, "String value"};
	printf("Member databaseNode0 has id %d with string value: %s \n", databaseNode0.id, databaseNode0.stringValue); //Member databaseNode0 has id 1 with string value: String value
}
```

**Size**: ``struct`` has the size of its all data member

Example:

```c
struct databaseNode databaseNode0 = {1, "String value"};
printf("size %d", sizeof(databaseNode0)); //56
```

Size ``104 = id (int) + stringValue[50]``

### Object from struct

Set up value for struct's member

```c
#include <stdio.h>
#include <string.h> // for strcpy

struct databaseNode {
	int id;
	char stringValue[50];
} databaseNode0;

main(){
	strcpy(databaseNode0.stringValue, "Name"); //to set variable with char in struct
	databaseNode0.id = 2;
	printf("Member databaseNode0 has id %d with string value %s \n", databaseNode0.id, databaseNode0.stringValue);
}
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