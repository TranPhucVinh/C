Bit field defines the maximum bit that a variable can store in a struct. This will save the memory of a struct.

### Examples


### Overflow issue 

```c
struct databaseNode {
    int number1:2;
    int number2:3;
};

    struct databaseNode databaseNode0 = {3, 7};
	printf("number1 is %d and number2 is %d\n", databaseNode0.number1, databaseNode0.number2);//-1 and -1
}
```

**Explain**

As ``3 = 0b11`` while ``int`` in GCC use 4 bytes to store the value so the rest of the byte are set with ``1`` bit.

So ``3`` then will be presented by ``1111 1111`` by ``int number1:2``, ``1111 1111`` is also ``-1``.

The same problem happens with ``7`` for ``int number2:3``.

For bigger value

```c
struct databaseNode databaseNode0 = {4, 8};
printf("number1 is %d and number2 is %d\n", databaseNode0.number1, databaseNode0.number2);//0 and 0
```

``4`` (0b100) with ``int number1:2`` will be presented as ``1111 1100`` which is ``-0``.

```c
struct databaseNode databaseNode0 = {5, 9};
printf("number1 is %d and number2 is %d\n", databaseNode0.number1, databaseNode0.number2);//1 and 1
```

### Problem solve

Use the total byte which is bigger than 1 of the storage value.

E.g: Use ``int number1:3`` for ``3``

```c
struct databaseNode {
        int number1:3;
        int number2:4;
    };

struct databaseNode databaseNode0 = {3, 7};
printf("number1 is %d and number2 is %d\n", databaseNode0.number1, databaseNode0.number2);//3 and 7
```