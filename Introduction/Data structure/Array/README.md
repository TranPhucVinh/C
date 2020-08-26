### Introduction

* An array is collection of items stored at **continuous memory** locations.
* The size of array in C is compulsory, not like ``array[]`` in JavaScript.

### Features

An array support those features:

* Create
* Read
* Update
* Delete

Example:

**Create**

* Create array: ``create_array.c``
* Create new member from index: ``create_new_member.c``

**Read**
* Simply read from ``index`` with ``array[index]``

**Update**

* Update value for array member from index: ``array[index] = new_value``

**Delete**

* Delete member in array from index: ``delete.c`` 

### size of an array

Print out all member in array without passing in its array size in for loop

```c
int array[] = {1, 2, 3};
size_t arraySize = sizeof(array)/sizeof(array[0]);
```

``size_t arraySize = sizeof(array)/sizeof(array[0]);`` can also be returned with ``sizeof(array)/sizeof(int)``.

### Fail in dynamic array

Enter the size of array

```c
int i, n, array[n];
printf("Enter the number of members: ");
scanf("%d", &n);
printf("Enter the value of each member: ");
	
for (i = 0; i < n; i++){
   scanf("%d", &array[i]);
}
 
for (i=0; i < n; i++){
   printf("Value of member %d is %d \n", i, array[i]);
}
```

**Result**

```
Segmentation fault (core dumped)
```

### Multi-dimension array

**Example 1**

```c
int a[3][4] = {  
   {0, 1, 2, 3} ,   /*  initializers for row indexed by 0 */
   {4, 5, 6, 7} ,   /*  initializers for row indexed by 1 */
   {8, 9, 10, 11}   /*  initializers for row indexed by 2 */
};

printf("%d: ", a[2][3]); //11
```

**Example 2**: Multiple string with 2-dimension array

```cpp
#include <stdio.h>

char ch_arr[3][10] = {
                         "spike",
                         "tom",
                         "jerry"
                     };

main() {
	for (int i=0; i < 3; i++){
		printf("string: %s \n", ch_arr + i);
	}
}
```

**Output**

```
string: spike 
string: tom 
string: jerry 
```