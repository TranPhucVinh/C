Two pointers is a technique to use 2 pointers, one at the beginning of a sequence (array, string, linked list), and the left one at any other position in the sequence, e.g the end of that sequence, to start searching for a specific item, pattern.

# Check for a specific sum in a sorted array

This problem is mostly known as **two sum**: Given an array in ascending order, find two numbers such that they add up to a specific target number.

With two pointer technique:

```cpp
int *start_ptr = &numbers[0];// The start pointer starts at the 1st index of the array
int *end_ptr = &numbers[numbers.size()-1];// The end pointer starts at the end index of the array
```

As the array is ascending:
* If ``(*start_ptr + *end_ptr) > target``, we will go backward in the array by one index so search for a smaller sum of ``*start_ptr + *end_ptr``. So ``end_ptr--``.
* If ``(*start_ptr + *end_ptr) < target``, we will go upward in the array by one index so search for a bigger sum of ``*start_ptr + *end_ptr``. So ``start_ptr--``.

Program:
```cpp
vector<int> twoSum(vector<int>& numbers, int target) {
    vector<int> found_index;
    int *start_ptr = &numbers[0];
    int *end_ptr = &numbers[numbers.size()-1];
    int start_ptr_index = 0;
    int end_ptr_index = numbers.size()-1;

    while (start_ptr_index != end_ptr_index ){
        if ((*start_ptr + *end_ptr) > target) {
            end_ptr--;
            end_ptr_index--;
        } else if ((*start_ptr + *end_ptr) < target){
            start_ptr++;
            start_ptr_index++;
        } else {
            found_index.push_back(start_ptr_index);
            found_index.push_back(end_ptr_index);
            return found_index;
        }  
    }
    // cout << start_ptr_index << " " << end_ptr_index << endl; 
    found_index.push_back(-1);
    found_index.push_back(-1);
    return found_index; 
}
```
# Implementations
* [Get the middle member of the linked list by 1 time traversing](https://github.com/TranPhucVinh/C/blob/master/Data%20structure/Linked%20list/Singly%20linked%20list/Read.md#get-the-middle-member-of-the-linked-list-by-1-time-traversing)
* [Verify if a given linked list is a circular linked list](https://github.com/TranPhucVinh/C/tree/master/Data%20structure/Linked%20list/Circular%20linked%20list#verify-if-a-given-linked-list-is-a-circular-linked-list)
