# Nested struct

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

# Form an ``uint16_t`` number from 2 ``uint8_t`` numbers with ``struct``

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

# [Use struct for string parsing](Use%20struct%20for%20string%20parsing.md)

* [Split a string into specific sequences]()
* [Parsing a hex char array]()
