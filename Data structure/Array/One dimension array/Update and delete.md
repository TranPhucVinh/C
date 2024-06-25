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
Right rotation means moving the last element of a sequence to its first.

Beside the normal approach to re-write the value in all array member, the best approach is to use the formular:

```c
int rotation_time = 1;
new_array[(i + rotation_time) % array_size] = old_array[i];
```
```c
void rotate(int *array, int arr_sz){
    int rotate_time = 1;

    int _tmp_array[arr_sz];

    memcpy(_tmp_array, array, sizeof(_tmp_array));

    for (int i = 0; i < arr_sz; i++){
        array[(i + rotate_time) % arr_sz] = _tmp_array[i];
    }
}
```
# Delete

* Delete member in array at specific index: [delete_at_index.c](delete_at_index.c)