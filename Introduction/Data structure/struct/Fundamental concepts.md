### Build a struct

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

Can define value like this way:
```c
struct databaseNode databaseNode0 = {
    .id = 1,
    .stringValue = "String value"
  };
```
This compile normally on GCC but gives error in G++:

```
error: C99 designator ‘stringValue’ outside aggregate initializer
};
```

### struct as array type

```c
#include <stdio.h>

struct databaseNode {
	int id;
	char stringValue[50];
};

int main(){
	struct databaseNode nodeArray[2];
	struct databaseNode databaseNode0 = {1, "Database node 0"};
	struct databaseNode databaseNode1 = {2, "Database node 1"};
	nodeArray[0] = databaseNode0;
	nodeArray[1] = databaseNode1;
	printf("nodeArray[0].id: %d, nodeArray[0].stringValue: %s\n", nodeArray[0].id, nodeArray[0].stringValue);
}
```

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