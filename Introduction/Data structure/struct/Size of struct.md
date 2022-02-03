## struct padding

**Note**:

* Padding is only added when a structure member is followed by a member with a larger size or at the end of the structure.
* Padding is used to fix the size of the largest data type, not to fix the whole register.

Size of struct calculation

**Example 1**

```c
struct databaseNode { 
    char a; //1 byte
    char b; //1 byte
    int c; //4 bytes
} node; 

printf("sizeof node %ld", sizeof(node)); //8
```

**Explain**

The variable are stacked in the memory like:

|Byte|0|1|2|3|
|--|--|--|--|--|
|char a, char b|a|b|**padding**|**padding**|
|int c|c|c|c|c|

As variable ``int c`` has the largest size (4 bytes), so two variable ``a``, ``b`` which come first has to be pad to fix 4 byte of variable ``c``

**Example 2**

```c
struct databaseNode { 
    char a; //1 byte
    int c; //4 bytes
    char b; //1 byte 
} node; 

printf("sizeof node %ld", sizeof(node)); //12
```

The variable are stacked in the memory like:

|Byte|0|1|2|3|
|--|--|--|--|--|
|char a|a|**padding**|**padding**|**padding**|
|int c|c|c|c|c|
|char b|b|**padding**|**padding**|**padding**|

### Data struct padding for string char

**Example**

```c
struct databaseNode
{
    int id;
    char stringValue[8];
} node;

printf("sizeof node %ld", sizeof(node)); //12
```

The size ``stringValue[8]`` here doesn't exceed the size of ``id`` as every char is stored in 1 byte.

```c
struct databaseNode
{
    int id;
    char stringValue[7];
} node;

printf("sizeof node %ld", sizeof(node)); //12
```

The variable are stacked in the memory like:

|Byte|0|1|2|3|
|--|--|--|--|--|
|int id|id|id|id|id|
|char stringValue[7]|stringValue|stringValue|stringValue|stringValue|
|char stringValue[7]|stringValue|stringValue|stringValue|**padding**|

## struct packing

Using struct padding will increase the performance of the system. However, size of struct now is bigger than the expected size which will increase the size of the program.

To control the program and also keep the well performance related to struct, **struct packing** technique is used.

In **struct packing** technique, **packsize** value is used.

If ``packsize >= size of the biggest member inside the struct``, struct packing is ignored.

If ``packsize < size of the biggest member inside the struct``, data alignment is then based on ``packsize``.

### Implementations

```c
#pragma pack(n) //(n = 1, 2, 4, 8, 16)
```

With ``packsize = 1``

```c
#include <stdio.h>

#pragma pack (1) //1 byte

struct database_node { 
   char a; //1 byte
   int c; //4 bytes
   char b; //1 byte 
} node;

int main()
{
   printf("size = %d\n", sizeof(node));//6
}
```

|Byte|0|
|--|--|
|char a|a|
|int c|c|
|int c|c|
|int c|c|
|int c|c|
|char b|b|

With ``packsize = 2``

```c
#pragma pack (2) //2 bytes
printf("size = %d\n", sizeof(node)); //8
```

|Byte|0|1|
|--|--|--|
|char a|a|**padding**|
|int c, int c|c|c|
|int c, int c|c|c|
|char b|b|**padding**|

With ``packsize = 4``

```c
#pragma pack (4) //4 bytes
printf("size = %d\n", sizeof(node));//12
```

### Disable struct padding

```c
struct databaseNode
{
    int id;
    char stringValue[7];
} __attribute__((packed)) node;

sizeof(node);//11
```