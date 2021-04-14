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

### Nested struct

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

### struct function

```c
struct databaseNode {
	int id;
	char stringValue[50];
};

struct databaseNode displayString();

main(){
   displayString();
}

struct databaseNode displayString(){
   struct databaseNode node0;

   printf("Hello, World !\n");
   return node0;
}
```