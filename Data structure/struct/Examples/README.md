## Example 1

Enter value for struct member using ``scanf()``

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

## Example 3

Form an ``uint16_t`` number from 2 ``uint8_t`` numbers with ``struct``.

```c
#include <stdio.h>
#include <stdint.h>

typedef struct
{
	uint8_t number_1;
	uint8_t number_2;
} struct_number;

struct_number number;

uint16_t number_3;

int main()
{
	number.number_1 = 0x12;
	number.number_2 = 0x34;

	number_3 = *(uint16_t*)(&number.number_1);
	printf("0x%x\n", number_3); //0x3412
}
```

## Use struct for string parsing

Check [Use struct for string parsing document](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/struct/Examples/Use%20struct%20for%20string%20parsing.md)