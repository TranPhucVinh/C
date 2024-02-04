# Syntax

* ``.``: access the instance inside a **struct object**
* ``->``: used by **pointer struct object** to access the value

# Struct pointer on stack memory

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

# Struct pointer on heap memory

**This is a wrong implementation with struct pointer and must be avoided**

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

**Note**: Not use ``node0 = (struct databaseNode *)malloc(sizeof(struct databaseNode*));``, as size of struct pointer is always ``8``, just like other data type.

# Pass by value and pass by reference with struct pointer

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
**Problem solved**: Using struct pointer

```c
void change_value(struct databaseNode *node);

int main(){
	struct databaseNode node = {1, "String value"};
   printf("%d %s \n", node.id, node.stringValue);//1 String value
	change_value(&node);
   printf("%d %s \n", node.id, node.stringValue);//100 Changed string
}

void change_value(struct databaseNode *node){
	node->id = 100;
   strcpy(node->stringValue, "Changed string");
}
```
