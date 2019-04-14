# Pointer vs Array

An array is a constant pointer.

### Example 1

Use pointer to get address and value of member of array

```c
int *p;
int arrayValue[3] ={1, 2, 3};
int main(){
   p = arrayValue;
   printf("p: %p \n", p);
   printf("arrayValue: %p \n", arrayValue);
   printf("address of pointer variable: %p \n", &p);
   printf("address of arrayValue : %p \n", &arrayValue);
   printf("p[0]: %d \n", p[0]);
   printf("*&p[0]: %d \n", *&p[0]);
   printf("p[0]: %d \n", p[0]);
   return(0);
}
```

**Result**

```
p: 0x601030 
arrayValue: 0x601030 
address of pointer variable: 0x601048 
address of arrayValue : 0x601030 
p[0]: 1 
*&p[0]: 1 
p[0]: 1 
```

The **address of an array** is also the **address of member 0** in array.

```c
printf("address of arrayValue : %p \n", &arrayValue);
printf("address of arrayValue[0] : %p \n", &arrayValue[0]);
```

**Result**

```
address of arrayValue : 0x601030 
address of arrayValue[0] : 0x601030 
```

**Use pointer in array to enter the value in array**

```c
#include <stdio.h>

void enterArray(int *array, int n){
	for (int i=0;i<n;i++){
		printf("Enter value array[%d]: \n",i );
		scanf("%d", &array[i]);
	}
}
void main() {
	int n;
	printf("enter number n");
	scanf("%d", &n);
	int array[n];
	enterArray(array, n);
}
```

### Example 2

Use pointer to enter the values in array and display these values on screen.

```c
#include <stdio.h>

void main() {
	int n, *p1, *p2, i;
	int a[20];
	printf(" Number of members in array: ");
	scanf("%d", &n);
	p1 = p2 = &a[0];
	printf("Enter the value of every member: " );
	for (i = 0; i < n; i++){
		scanf("%d", p1);
		p1++;
	}
	printf("Value of all members in array: ");
	for (i = 0; i < n; i++){
		printf("%d ", *p2 );
		p2++;
	}
}
```