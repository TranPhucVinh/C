# Update

* Update array member at specific index: ``array[index] = new_value``

## Insert a new member at specific index

**Precondition**: Size of the array to be inserted must bigger its total member

E.g 

```c
//Declare array with 100 member to first store 5 member
int array[100] = {1,3,5,7,8};
```

If the array size is fixed with its first total members, there will error later when inserting the new member because the array will then be extended to the unallocated memory location.

E.g

```c
//Declare array with 100 member to first store 5 member
int array[] = {1,3,5,7,8};

array[5] = 10;//Insert a new member at index 5, the unallocated location, result in memory segment fault
```

Program: [insert_member_at_index.c](insert_member_at_index.c)
 
## Rotate an array
**Left rotation** is moving the last element of a sequence to its first.

Beside the normal approach to re-write the value in all array member, the best approach is to use the formular:

```c
int rotation_time = 1;
new_array[(i + rotation_time) % array_size] = old_array[i];
```
**Right rotation** is moving the first element of a sequence to its last. The best approach for right rotation is this formular:
```c
int rotation_time = 1;
new_array[(i + array_size - rotation_time) % array_size] = old_array[i];
```
```c
void left_rotate(int *array, int arr_sz){
    int rotate_time = 1;

    int _tmp_array[arr_sz];

    memcpy(_tmp_array, array, sizeof(_tmp_array));

    for (int i = 0; i < arr_sz; i++){
        array[(i + rotate_time) % arr_sz] = _tmp_array[i];
    }
}

void right_rotate(int *array, int arr_sz){
    int rotate_time = 1;

    int _tmp_array[arr_sz];

    memcpy(_tmp_array, array, sizeof(_tmp_array));

    for (int i = 0; i < arr_sz; i++){
        array[(i + arr_sz - rotate_time) % arr_sz] = _tmp_array[i];
    }
}

/* Result:
   int arr[] = {1, 2, 3, 4, 5, 6};
   left_rotate(arr, 6);// arr = 6 1 2 3 4 5
   right_rotate(arr, 6);// arr = 2 3 4 5 6 1
*/
```
## Reorder an array
Reorder an array from ``L0 → L1 → … → Ln - 1 → Ln`` to ``L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …``

```c
#include <stdio.h>

#define SIZE 4
// #define SIZE 5

void main() {
    int array[SIZE] = {1, 2, 3, 4};
    // int array[SIZE] = {1, 2, 3, 4, 5};

	for (int i=0; i < SIZE; i++){
		printf("%d ", array[i]);
	}
    printf("\n");

    int new_arr[SIZE];

    // Form new_arr at even position
    int _iterate = 0;
    for (int i = 0; i < SIZE; i = i+2) {
        new_arr[i] = array[_iterate];
        _iterate += 1;
    }

    _iterate = 0;

    // Form new_arr at odd position
    for (int i=1; i < SIZE; i=i+2) {
        new_arr[i] = array[SIZE - 1 - _iterate];
        _iterate += 1;
	}

    for (int i=0; i < SIZE; i++){
		printf("%d ", new_arr[i]);
	}
}
```
# Delete

* Delete member in array at specific index: [delete_at_index.c](delete_at_index.c)
