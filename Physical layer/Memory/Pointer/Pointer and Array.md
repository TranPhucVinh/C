An array is a constant pointer.

### Example 1

Use pointer to get address and value of member of a one dimension array

```c
#include <stdio.h>

int *p;
int arrayValue[3] = {1, 2, 3};

int main(){ 
	p = arrayValue;
	printf("%p \n", p); //0x601038
	printf("%p \n", arrayValue); //0x601038
	printf("%p \n", &arrayValue); //0x601038
	printf("%p \n", &arrayValue[0]); //0x601038
	printf("%d \n", p[0]); //1
	printf("%d \n", &p[0]); //6295608 = 0x601038
	printf("%p \n", &p[0]); //0x601038
	printf("%d \n", *&p[0]); //1
	return(0);
}
```

**Note**: The **address of an array** is also the **address of member 0** in array.

The same result for string char

```c
char displayedString[] = "Hello, World!";

printf("%p\n", displayedString); //0x7fff8ab00140
printf("%p\n", &displayedString);//0x7fff8ab00140
printf("%s\n", *&displayedString);//Hello, World!
```
Get value of by index of an array by pointer
```c
int array[] = {1, 342, 3};
printf("%d ", *(array+0));
```

Use pointer to get value of a multidimension array:

```c
int (*array_pointer)[3];
int array[2][3] = {{0, 1}, {2, 3}};

array_pointer = array;
printf("%d %d\n", array_pointer[0][0], array_pointer[1][1]);//0 3
```