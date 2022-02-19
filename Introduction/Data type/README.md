## Data type

| Type | Storage size|Value range|
| ------- |------|------|
|char |1 byte|-128 to 127 or 0 to 255|		
|unsigned char |1 byte|0 to 255|		
|signed char |1 byte|-128 to 127|		
|int |2 or 4 bytes|-32,768 to 32,767 or -2,147,483,648 to 2,147,483,647|		
|unsigned int |2 or 4 bytes|0 to 65,535 or 0 to 4,294,967,295|		
|short |2 bytes|-32,768 to 32,767|		
|unsigned short	 |2 bytes|0 to 65,535|
|long	 |8 bytes|-9223372036854775808 to 9223372036854775807|		
|unsigned long|8 bytes|0 to 18446744073709551615|		

With Microsoft C++ 32-bit and 64-bit compilers, int has the range -2,147,483,648 to 2,147,483,647.

``GCC`` and ``G++`` define int as 4 bytes. Size of ``int`` different from various compiler of the MCU.

In ``GCC`` and ``G++``, the default ``char`` type is ``signed char``. If compile by ``MSVC`` with ``/J`` option, ``char`` will switch to ``unsigned char``.

``E`` is for power of 10. E.g:

```c
int number = 4E2;
printf("%d\n", pid);//400
```

### Endianness

**Endianness** is the order or sequence of bytes of a word of digital data in computer memory. Endianness is primarily expressed as **big-endian (BE)** or **little-endian (LE)**. A big-endian system stores the most significant byte of a word at the smallest memory address and the least significant byte at the largest. A little-endian system, in contrast, stores the least-significant byte at the smallest address.

### const

``const`` is used to define constant variable and can't be changed

E.g: ``const int a = 19``

To change ``const`` variable: ``Pointer/Examples.md`` -> ``Example 1.3: Change value of a variable with pointer``

Local ``const`` variable inside a function is fine and gives no issue:

```c
#include <stdio.h>

int const_test(int a){
    const int b = a;
    return b;
}

int main(int argc, char *argv[]) {
    printf("%d\n", const_test(1));//1
    printf("%d\n", const_test(2));//2
    printf("%d\n", const_test(3));//3
}
```

### auto

``auto`` is used to defined local variable

```c
void printFunction(){
	int auto a = 19;
	printf("%d ", a);
}
```

### extern

``extern`` variables are also known as global variables, they are variables defined outside any function block. 

Access global variable if there is a local variable with same name:

```c
int x = 50; // Global x
 
int main()
{
    int x = 10; // Local x
    {
        extern int x;
        printf("Value of global x is %d\n", x);
    }
    printf("Value of local x is %d\n", x);
    return 0;
}
```
**Note**
Must have ``{}``, without ``{}`` there will be error 

```
error: extern declaration of ‘x’ follows declaration with no linkage
         extern int x;
```

### sizeof()

Return the amount of memory allocated to that data type in **byte**.

**Size of all data type**

```c
int a = 16;
printf("Size of variable a: %d\n", sizeof(a)); //Size of variable a : 4
printf("Size of int data type: %d\n", sizeof(int)); //Size of int data type : 4
printf("Size of int*: %d\n", sizeof(int*)); //Size of int*: 8
printf("Size of char data type: %d\n", sizeof(char)); //Size of char data type : 1
printf("Size of float data type: %d\n", sizeof(float)); //Size of float data type : 4
printf("Size of double data type: %d\n", sizeof(double)); //Size of double data type : 8     
```

**Size in array**

```c
int hello[] = {1, 2, 3};
char charHello[] = "";
char hw[] = "Hello, World!";
printf("sizeof: %d \n", sizeof(hello));
printf("sizeof: %d \n", sizeof(charHello));
printf("sizeof: %d \n", sizeof(hw));
```

```
sizeof: 12 (3 int number has total 12 byte)
sizeof: 1 
sizeof: 14
```
