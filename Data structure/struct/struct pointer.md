# Syntax

* ``.``: access the instance inside a **struct object**
* ``->``: used by **pointer struct object** to access the value

# Struct pointer on stack memory

Create a struct pointer: Use a struct pointer object to set value for a struct object

```c
#include <stdio.h>

struct StructObject {
	int id;
	char str_val[50];
};

int main()
{
    struct StructObject *ptr_obj;
    struct StructObject obj = {1, "Hello, World !"};
    ptr_obj = &obj;

    printf("ptr_obj:\n");
    printf("ID: %d\n", ptr_obj->id);
    printf("str_val: %s\n", ptr_obj->str_val);

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

# Pass by value; pass by reference with struct pointer

**Pass by value**: Passing a struct by value as a function argument to change its member's value won't give effect:

```c
#include <stdio.h>
#include <string.h>

struct StructObject {
	int id;
	char str_val[50];
};

void change_value(struct StructObject obj);

int main(){
	struct StructObject obj = {1, "String value"};
   printf("before: id is %d and string value is %s \n", obj.id, obj.str_val);//before: id is 1 and string value is String value
	change_value(obj);
   printf("after: id is %d and string value is %s \n", obj.id, obj.str_val);//after: id is 1 and string value is String value 
}

void change_value(struct StructObject obj){
	obj.id = 100;
    strcpy(obj.str_val, "Change string");
}
```
**Problem solved**: Use struct pointer

```c
void change_value(struct StructObject *obj);

int main(){
	struct StructObject obj = {1, "String value"};
    printf("before: id is %d and string value is %s \n", obj.id, obj.str_val);//before: id is 1 and string value is String value
	change_value(&obj);
    printf("after: id is %d and string value is %s \n", obj.id, obj.str_val);//after: id is 1 and string value is String value 
}

void change_value(struct StructObject *obj){
	obj->id = 100;
    strcpy(obj->str_val, "Change string");
}
```
