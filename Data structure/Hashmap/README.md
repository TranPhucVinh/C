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