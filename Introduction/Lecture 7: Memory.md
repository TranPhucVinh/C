# memset()

Include in library **string.h**.

``memset()`` copies the character **c** (an unsigned char) to the first **n** characters of the string pointed to, by the argument **str**.

It can also be inferred as **filling a block of memory with a particular value**. Where **str** is starting address of memory to be filled, **c** is the value to be filled, and **n** is **number of bytes** to be filled starting from **ptr** to be filled.

**Prototype**

```c
void *memset(void *str, int c, size_t n)
```

## memset() with string

```c
int main(){
    char str[] = "C programming with GNU-GCC";
    memset(str,'$',7);
    puts(str);
}
```

**Result**

```
$$$$$$$amming with GNU-GCC
```

If ``memset(str,'$',0);``, the **result** will be:

```
C programming with GNU-GCC
```

**Compare to ASCII number**

```c
int main() {
    char str[] = "C programming with GNU-GCC";
    memset(str, 48, 7);
    puts(str);
}
```
**Result**

```
0000000amming with GNU-GCC
```

Number 48 correspond to character **0** in ASCII code.

## memset() with address

```c
int main() {
	int a = 9;

	printf("value a before: %d \n", a);
    memset(&a, 'a', 0);
    printf("value a after: %d \n", a);
}    
```

**Result**

```
value a before: 9 
value a after: 9 
```

This program set the value in **memory** of variable **a** with new value **'a'** from 0 **character**.

**filled with 1 byte**: 

```c
memset(&a, 'a', 1);
```

**Result**

```
value a before: 9 
value a after: 97 
```

``'a'`` has ASCII code ``97`` (``01100001``).

**filled with 2 byte**: 

```c
memset(&a, 'a', 2);
```

**Result**

```
value a before: 9 
value a after: 24929 
```

24929 = 110000101100001 = 01100001 + 01100001 = 'a' (ASCII code)  + 'a' (ASCII code)

## memset() handle with int overflow

```c
memset(&a, 'a', 4);
```

**Result**

```
value a before: 9 
value a after: 1633771873 
```

1633771873 = 1100001011000010110000101100001 (16 bit-4 byte)

**4 byte** is the maximum value that an integer number can store.

```c
memset(&a, 'a', 5);
```

The value of a is now still ``1633771873``.

This overflow bit will affect other variable value in memory.

**Example**

```c
struct student{
		int id;
		char name[50];
		char classroom[50];
};

int main() {
	int a = 9;
	struct student erin = { 1977, " Erin", "Free Lancer" };

	printf("value &a: %p \n", &a);
	printf("value &erin before: %p \n", &erin);

	printf("value a before: %d \n", a);
    memset(&a, 'a', 4);
    printf("value a after: %d \n", a);

    printf("value erin.id before: %d \n", erin.id);
}
```

```
value &a: 0x7fff03bba02c 
value &erin before: 0x7fff03bba030 
value a before: 9 
value a after: 1633771873 
value erin.id before: 1977 
```

Value of **erin.id** now isn't effected by ``memset(&a, 'a', 4)`` return the expected value ``1977``.

With ``memset(&a, 'a', 5)``, the result will be

```
value a before: 9 
value a after: 1633771873 
value erin.id before: 1889 
```

**erin.id** now is effected due to the overflow value of ``memset(&a, 'a', 5)``.

### memset() problem with 4 byte number

```c
int main() {
	int a = 1977;
	memset(&a, 'a', 1);
	printf("value a after memset(): %d \n", a);
}
```

```
value a after memset(): 1889 (expected 97)
```

```
1977 = 0000 0111 1011 1001;
97 =  0000 0000 0110 0001;
1889 = 0000 0111 0110 0001;
```

1889 has its left 1 byte is **97** (**0110 0001**) and the its  first 1 byte is still **0000 0111**.

With ``memset(&a, 'a', 2)``, the result will be ``24929``, as now 2 byte are completely replace with 2 character **'a'**.

### memset() with struct

```c
struct student{
		int id;
		char name[50];
		char classroom[50];
};

int main() {
	struct student erin = { 1977, " Erin", "Free Lancer" };

    printf("value erin.id before: %d \n", erin.id);
    memset(&erin.id, 'a', 2);
    printf("value erin.id after: %d \n", erin.id);

     printf("value erin.id before: %s \n", erin.name);
    memset(&erin.name, 'a', 2);
    printf("value erin.id after: %s \n", erin.name);
}
```

```
value erin.id before: 1977 
value erin.id after: 24929 
value erin.name before:  Erin 
value erin.name after: aarin 
```