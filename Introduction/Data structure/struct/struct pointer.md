### struct pointer

Create a struct pointer: Use a struct pointer object to set value for a struct object

```c
#include <stdio.h>

struct databaseNode
{
   int id;
   int intValue;
};

int main()
{
    struct databaseNode *databaseNodePtr, databaseNode1;
    databaseNodePtr = &databaseNode1;

    printf("Enter ID: ");
    scanf("%d", &databaseNodePtr->id);

    printf("Enter int value: ");
    scanf("%d", &databaseNodePtr->intValue);

    printf("databaseNode1:\n");
    printf("ID: %d\n", databaseNode1.id);
    printf("intValue: %d\n", databaseNode1.intValue);

    return 0;
}
```

Problem solved with struct pointer: ``Physical layer/Memory/Pointer/struct pointer.md``

### Struct pointer set value issue

```c
#include <stdio.h> 
#include <stdlib.h>
  
struct databaseNode { 
    int id;
    int intValue;
}; 

int main() 
{ 
    struct databaseNode *node0;
    node0->id = 1;
    node0->intValue = 100;
    return 0; 
} 
```
**Output**: ``Segmentation fault``

Problem solved:

```c
node0 = (struct databaseNode *)malloc(sizeof(struct databaseNode));

node0->id = 1;
node0->intValue = 100;
```