# Implement by recursive
```c
#include <stdio.h>
#include <stdbool.h>

bool found = false;// Mark if the target is found

/*
    Return:
    * Index of the found target
    * the index when binary search recursive function search_number()
      ends when target is inside [lower bound, upper bound]
*/
int search_number(int target, int *array, int start_index, int end_index) {
    int middle = 0;
    if (start_index == end_index) {
        if (target == array[start_index]){
            found = true;
            return start_index;
        } else {
            found = false;
            return start_index;
        }
    }
    middle = (start_index + end_index)/2;// Middle index
    if (target == array[middle]) {
        found = true;
        return middle;
    }
    else if (target > array[middle]){
        return search_number(target, array, middle+1, end_index);
    } else {
        return search_number(target, array, start_index, middle);
    }
    
    return 0;
}

#define TARGET 1

int main(){
    int arr[] = {1, 2, 5, 12, 34};
    int arr_sz = sizeof(arr)/sizeof(int);
    int ret = search_number(TARGET, arr, 0, arr_sz-1);
    if (found) printf("%d found at %d\n", TARGET, ret);
    else {
        // When ret is 0, TARGET is < lower bound of the array
        if (!ret) printf("%d isn't found as it is less than the lower bound\n", TARGET);      
        if (ret == arr_sz - 1) printf("%d isn't found as it is bigger than the lower bound\n", TARGET);

        printf("%d isn't found while it inside range [lower bound, upper bound]\n", TARGET);
    }
}
```
# Implement by looping
```c
int search_number(int target, int *array, int start_index, int end_index) {
    int middle = 0;

    while (start_index <= end_index){
        if (start_index == end_index) {
            if (target == array[start_index]){
                printf("%d found at %d\n", target, start_index);
                return target;
            } else {
                printf("%d not found\n", target);      
                return -1;
            }
        }
        middle = (start_index + end_index)/2;// Middle index

        if (target == array[middle]) {
            printf("%d found at %d\n", target, middle);
            return target;
        }

        else if (target > array[middle]){
            start_index = middle+1;
            continue;
        } else {
            end_index = middle;
            continue;
        }
    }
    return 0;
}

int main(){
    int arr[] = {1, 2, 5, 12, 34};
    int arr_sz = sizeof(arr)/sizeof(int);
    search_number(34, arr, 0, arr_sz-1);
}
```
# Count total occurence of a number inside a sorted array

As the array is sorted, so the best approach is to find the index of the 1st occurrence of that number, then find the index of the last one.

## Find index of the 1st occurrence of a number inside a sorted array
```cpp
int first_occurrence = -1; // Index of the first occurrence

int find_first_occurrence(int target, int *array, int start_index, int end_index) {
    int middle = 0;
    if (start_index == end_index) {
        if (target == array[start_index]){
            first_occurrence = start_index;
        } else {
            if (first_occurrence == -1) printf("%d not found\n", target);
        }
        return first_occurrence;
    }

    middle = (start_index + end_index)/2;// Middle index
    if (target == array[middle]) {
        first_occurrence = middle;
        return find_first_occurrence(target, array, start_index, middle);;
    }
    else if (target > array[middle]){
        return find_first_occurrence(target, array, middle+1, end_index);
    } else {
        
        return find_first_occurrence(target, array, start_index, middle);
    }
    
    return first_occurrence;
}
```
## Find index of the last occurrence of a number inside a sorted array
```c
int last_occurrence = -1; // Index of the first occurrence

int find_last_occurrence(int target, int *array, int start_index, int end_index) {
    int middle = 0;
    if (start_index == end_index) {
        
        if (target == array[start_index]){
            last_occurrence = start_index;
        } else {
            if (last_occurrence == -1) printf("%d not found\n", target);
        }
        return last_occurrence;
    }

    middle = (start_index + end_index)/2;// Middle index

    if (target == array[middle]) {
        last_occurrence = middle;
        return find_last_occurrence(target, array, middle+1, end_index);
    }
    else if (target > array[middle]){
        return find_last_occurrence(target, array, middle+1, end_index);
    } else {        
        return find_last_occurrence(target, array, start_index, middle);
    }
    
    return last_occurrence;
}
```
## Count total occurence of a number inside a sorted array
```cpp
#define NUMBER 6

int main(){
    int arr[] = {2, 4, 6, 6, 6, 10, 20};
    int arr_sz = sizeof(arr)/sizeof(int);
    int first_occurrence = find_first_occurrence(NUMBER, arr, 0, arr_sz-1);
    int last_occurrence = find_last_occurrence(NUMBER, arr, 0, arr_sz-1);  
    printf("Total %d", last_occurrence - first_occurrence + 1);
}
```