```c
void *memset(void *str, int c, size_t n)
```

``memset()`` copies the character ``c`` (unsigned char) to the first ``n`` characters of the string pointed to ``str``.

``memset()`` locates in ``string.h``.

### memset() with string

```c
char str[] = "C programming with GNU-GCC";
memset(str,'$',7); //$$$$$$$amming with GNU-GCC
```

**Compare to ASCII number**

```c
char str[] = "C programming with GNU-GCC";
memset(str, 48, 7); //0000000amming with GNU-GCC
```

Number 48 correspond to character **0** in ASCII code.

### memset() with address ``&``

This program set the value in memory of variable ``a`` with new value 'a' from ``0`` character.

```c
int a = 9;
printf("value a before: %d \n", a);// value a before: 9 
memset(&a, 'a', 1);
printf("value a after: %d \n", a);// value a after: 97 
```

Notice that: ``'a'`` has ASCII code ``97`` (``0110 0001``).

So ``memset(&a, 'a', 2)``: will give the result: ``value a after: 24929``.

Explain:

``24929 = 0110 0001 0110 0001``

### Change const variable with memeset()

Change ``const`` variable with ``memset()``

```c
const int a = 10;
memset(&a, 'a', 1);
```

**Result**

Compile with ``gcc`` gives warning:

```
warning: passing argument 1 of ‘memset’ discards ‘const’ qualifier from pointer target type [-Wdiscarded-qualifiers]
```

Compile with ``g++`` gives error:

```
error: invalid conversion from ‘const void*’ to ‘void*’ [-fpermissive]
    memset(&a, 'a', 1);
```
**Problem solved**

```c
volatile const int a = 10;
memset((void*)&a, 'a', 1);
```

### Overflow memset()

```c
memset(&a, 'a', 4);
```

**Result**

```
value a before: 9 
value a after: 1633771873 
```

``1633771873 = 0110 0001 0110 0001 0110 0001 0110 0001`` (**16 bit-4 byte**)

**4 byte** is the maximum value that an integer number can store.

```c
memset(&a, 'a', 5);
```

The value of a is now still ``1633771873``.

This overflow bit will **affect other variable value in memory**.

**Example**

The overflow issue with normally declared for 2 consecutive variables:

```c
int a = 9;
int id = 1977;

printf("value a before: %d \n", a); //value a before: 9 
memset(&a, 'a', 5);
printf("value a after: %d \n", a); //value a after: 1633771873 

printf("id: %d \n", id); //1889 
```

The overflow issue with ``struct``:

```c
struct student{
		int id;
		char name[50];
};

int main() {
	int a = 9;
	struct student erin = {1977, " Erin"};

	printf("value a before: %d \n", a); //value a before: 9 
    memset(&a, 'a', 4);
    printf("value a after: %d \n", a); //value a after: 1633771873 

    printf("value erin.id: %d \n", erin.id); //value erin.id: 1977 
}
```

Value of ``erin.id`` now isn't effected by ``memset(&a, 'a', 4)`` return the expected value ``1977``.

With ``memset(&a, 'a', 5)``, the result will be

```
value a before: 9 
value a after: 1633771873 
value erin.id: 1889
```

``erin.id`` now is effected due to the overflow value of ``memset(&a, 'a', 5)``.

### memset() problem with 4 byte number

```c
int a = 1977;
memset(&a, 'a', 1);
printf("value a after memset(): %d \n", a); //value a after memset(): 1889 (expected 97-ASCII code of 'a')
```

**Exaplain**

```
1977 = 0000 0111 1011 1001;
97 =  0000 0000 0110 0001;
1889 = 0000 0111 0110 0001;
```

1889 has its right 1 byte is ``97`` (``0110 0001``) and its left 1 byte is still ``0000 0111``.

With ``memset(&a, 'a', 2)``, the result will be ``24929``, as now 2 byte are completely replace with 2 character ``a``.
