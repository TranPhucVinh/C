A dangling pointer is a pointer pointing to a memory location that has been deleted (or freed).

# Dangling pointer when trying to point to de-allocated heap memory
```c
int* ptr = (int *)malloc(sizeof(int));
 
free(ptr);//ptr now is a dangling pointer
```

# Dangling pointer when trying to call local function variable 

```c
#include <stdio.h>

int* fun()
{
	int x = 5;
	return &x;
}

int main()
{
	int *p = fun();
	printf("%d", *p);//Segmentation fault
	return 0;
}
```
Using static won't make ``*p`` a dangling pointer

```c
#include <stdio.h>

int* fun()
{
	static int x = 5;
	return &x;
}

int main()
{
	int *p = fun();
	printf("%d", *p);//5; *p is a normal pointer now/isn't a dangling pointer
	return 0;
}
```
