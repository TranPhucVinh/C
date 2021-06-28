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