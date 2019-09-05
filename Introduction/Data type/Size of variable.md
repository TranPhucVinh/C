### sizeof()

Return the amount of memory allocated to that data type in byte.

**Example 1**

```c
int a = 16;
printf("Size of variable a : %d\n",sizeof(a));
printf("Size of int data type : %d\n",sizeof(int));
printf("Size of char data type : %d\n",sizeof(char));
printf("Size of float data type : %d\n",sizeof(float));
printf("Size of double data type : %d\n",sizeof(double));    
```   

```
Size of variable a : 4
Size of int data type : 4
Size of char data type : 1
Size of float data type : 4
Size of double data type : 8
```

**Example 2**

```c
int hello[] = {1, 2, 3};
char charHello[] = "";
printf("sizeof: %d \n", sizeof(hello));
printf("sizeof: %d \n", sizeof(charHello));
```

```
sizeof: 12 (3 int number has total 12 byte)
sizeof: 1 
```
