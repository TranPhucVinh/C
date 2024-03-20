# Count total duplicate numbers inside a sorted array

```c
#include <stdio.h>

int arr[] = {5, 7, 9, 9, 10, 11, 13, 13, 13, 16};
int hash_table[17];

void main(void)
{
    for (int i = 0; i < sizeof(arr)/sizeof(int); i++){
        hash_table[arr[i]] += 1; 
    }

    for (int i = 0; i < 17; i++){
        printf("%d ", hash_table[i]);
    }
    printf("\n");
}
```
This is an inefficient implementation of hash map as ``hash_table[17]`` has many un-used index. [Unordered map](https://github.com/TranPhucVinh/Cplusplus/blob/master/Data%20structure/Unordered%20map.md#use-unordered-map-to-count-total-duplicate-numbers-inside-an-array) is the best approach for it.
