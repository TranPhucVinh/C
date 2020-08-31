### How does CPU access a variable ?

A 8-bit CPU can access a 1 byte (8-bit) variable in 1 CPU cyle. So for a n-byte variable, it takes the CPU ``n`` CPU cycle to access

A 64-bit CPU can access a 8 byte (64-bit) variable in 1 CPU cyle. So for a 8*n byte variable, it takes the CPU ``n`` CPU cycle to access

**Note**: 64-bit CPU is used for the following programs execution.

### Data struct padding

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