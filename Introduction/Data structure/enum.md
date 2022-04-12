### enum

```c
enum {value0 = 10, value1, value2, value3, value4 = 10, value5 = 16, value6};
enum {value7, value8, value9, value10, value11=1, value12=12, value13};

printf("The value of the first enum: %d, %d, %d, %d, %d, %d, %d\n", value0 , value1, value2, value3, value4, value5, value6);
printf("The value of the second enum: %d, %d, %d, %d, %d, %d, %d", value7 , value8, value9, value10, value11, value12, value13);
```

```
The value of the first enum: 10, 11, 12, 13, 10, 16, 17
The value of the second enum: 0, 1, 2, 3, 1, 12, 13
```
**Notice**: After declaring the ``enum``, all variable inside ``enum`` (``value0``, ``value1``, ...) are all constant and unique.

Add name to ``enum`` and declare object

```c
enum enumObject {value0 = 10, value1, value2, value3, value4 = 10, value5 = 16, value6};
enum enumObject enumObject0;
```

### object of enum

```c
enum {
    value0 = 10, 
    value1
} node0;

printf("value of node0 before: %d \n", node0); //0
node0 = value1;
printf("value of node0 after: %d \n", node0); //1
```

Garbage value of enum object

```c
typedef enum {
    value0 = 30, 
    value1
} nodeObject0, nodeObject1, nodeObject2, nodeObject3, nodeObject4;

nodeObject0 node0;
printf("Garbage value of node0: %d \n", node0);
nodeObject1 node1;
printf("Garbage value of node1: %d \n", node1);
nodeObject2 node2;
printf("Garbage value of node2: %d \n", node2);
nodeObject3 node3;
printf("Garbage value of node3: %d\n", node3);
nodeObject4 node4;
printf("Garbage value of node4: %d\n", node4);
```

```
Garbage value of node0: 0
Garbage value of node1: 16
Garbage value of node2: 0
Garbage value of node3: 7611296
Garbage value of node4: 0
```
