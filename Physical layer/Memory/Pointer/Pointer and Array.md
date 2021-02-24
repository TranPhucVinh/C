# Pointer vs Array

An array is a constant pointer.

### Example 1

Use pointer to get address and value of member of array

```c
#include <stdio.h>

int *p;
int arrayValue[3] = {1, 2, 3};

int main(){ 
	p = arrayValue;
	printf("%p \n", p); //0x601038
	printf("%p \n", &p); //0x601050
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
char displayString[] = "Hello, World!";

printf("%p\n", displayString); //0x7fff8ab00140
printf("%p\n", &displayString);//0x7fff8ab00140
```

### Example 2

Use pointer in array to enter the value in array

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

### Example 3

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

### struct

```c
struct student{
		int id;
		char name[50];
		char classroom[50];
};

int main() {
	struct student erin = { 1977, " Erin", "Free Lancer" };

	printf("value &erin: %p \n", &erin); //0x7ffe09debe80
	printf("value &erin.id: %p \n", &erin.id); //0x7ffe09debe80
	printf("value &erin.name: %p \n", &erin.name); //0x7ffe09debe84
	printf("value &erin.classroom: %p \n", &erin.classroom); //0x7ffe09debeb6
}
```

Address of ``erin`` and ``erin.id`` are the same.