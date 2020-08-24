### Memory problem with struct

Check ``Overflow memset()`` in ``Physical layer/Memory/memset.md``

### struct pointer

Create a struct pointer

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

    printf("databaseNode:\n");
    printf("ID: %d\n", databaseNodePtr->id);
    printf("intValue: %d", databaseNodePtr->intValue);

    return 0;
}
```

Problem solved with struct pointer: ``Physical layer/Memory/Pointer/struct pointer.md``