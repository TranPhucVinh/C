# Binary search
Binary search is used to search for a specific member inside an ascending order array. This search method has the time complexity of O(log(n)) which is faster than the linear search method to iterate through every member of the array, which results in O(n).

Generally, binary search will chopping the half the array and search at the middle of it for every time searching, until it finds out the searched target.

For an ascending order array, binary search will search by searching at the middle of that array. If not match and:
* If array[middle] > target, it will start search at the middle of the 1/2 part of the array, starting from index 0 to index middle/2.
* If array[middle] <> target, it will start search at the middle of the 1/2 part of the array, starting from index middle/2 to the last index of the array.

## Implement by recursive
```c
#include <stdio.h>

int search_number(int target, int *array, int start_index, int end_index) {
    int middle = 0;
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
        return search_number(target, array, middle+1, end_index);
    } else {
        return search_number(target, array, start_index, middle);
    }
    
    return 0;
}

int main(){
    int arr[] = {1, 2, 5, 12, 34};
    int arr_sz = sizeof(arr)/sizeof(int);
    search_number(34, arr, 0, arr_sz-1);
}
```
## Implement by looping
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
# Application

Calculate sqrt(x) without using the built-in function:

Given a non-negative integer x, return the square root of x rounded down to the nearest integer. The returned integer should be non-negative as well. E.g ``sqrt(8) = 2.82842`` is rounded to ``2``.

An in-efficient approach, which takes 9ms (calculated by Leetcode), is to use loop:

```c
int mySqrt(int x) {
    for (long long i = 0; i <= x; i++){
		if (x == 1) return 1;
		else if (i*i > x) return i - 1;
	}
    return 0;
}
```
Use binary search as a better approach which takes 0ms run time (calculated by Leetcode)
