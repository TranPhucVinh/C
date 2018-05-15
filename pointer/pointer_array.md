Array ``arr[20]`` with variable ``arr`` is the pointer that store the value of ``arr[0]``.

```c
#include <stdio.h>

void main() {
	int a[20];
	printf("address %p", &a);
}
```

```c
#include <stdio.h>

void main() {
	int a[20];
	printf("address %p \n", &a);
	printf("address %p \n", &a[0]);
}
```

**Result**

```
address 0x7ffe8012de00 
address 0x7ffe8012de00 
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

**Use pointer to enter the values in array and display these values on screen**

```c
#include <stdio.h>

void main() {
	int n, *p1, *p2, i;
	int a[20];
	printf(" Number of members in array: ");
	scanf("%d", &n);
	p1 = p2 = &a[0];
	printf("Enter the value of every member: " );
	for (i = 0; i < n; i++)
	{
		scanf("%d", p1);
		p1++;
	}
	printf("Value of all members in array: ");
	for (i = 0; i < n; i++)
	{
		printf("%d ", *p2 );
		p2++;
	}
}
```
