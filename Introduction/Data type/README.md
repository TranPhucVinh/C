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

## Compare

| C | JavaScript|
| ------- |:------:|
|int a = 8; | var a = 8;|
| printf("%d ",a)    | console.log(a)    |

### const

``const`` is used to define constant variable and can't be changed

E.g: ``const int a = 19``

### sizeof()

Return the amount of memory allocated to that data type in **byte**.

**Size of all data type**

```c
int a = 16;
printf("Size of variable a : %d\n",sizeof(a)); //Size of variable a : 4
printf("Size of int data type : %d\n",sizeof(int)); //Size of int data type : 4
printf("Size of char data type : %d\n",sizeof(char)); //Size of char data type : 1
printf("Size of float data type : %d\n",sizeof(float)); //Size of float data type : 4
printf("Size of double data type : %d\n",sizeof(double)); //Size of double data type : 8    
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