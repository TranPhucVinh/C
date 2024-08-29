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
    int start_ptr_index = 0;
    int end_ptr_index = numbers.size()-1;

    while (start_ptr_index != end_ptr_index ){
          if ((numbers[start_ptr_index] + numbers[end_ptr_index]) > target) {
            end_ptr_index--;
        } else if ((numbers[start_ptr_index] + numbers[end_ptr_index]) < target){
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
**Notes**: The condition for the above implementation is each number appears only 1 time.
# Check for a specific substract in a sorted array
```cpp
#include <iostream>
#include <vector>
#include <algorithm>    // std::sort

using namespace std;

vector<int> twoSubtraction(vector<int>& numbers, int target) {
    vector<int> found_index;
    int *start_ptr = &numbers[0];
    int *end_ptr = &numbers[numbers.size()-1];
    int start_ptr_index = 0;
    int end_ptr_index = numbers.size()-1;

    while (start_ptr_index != end_ptr_index ){
        if ((*end_ptr - *start_ptr) > target) {
            start_ptr++;
            start_ptr_index++;
        } else if ((*end_ptr - *start_ptr) < target){
            end_ptr--;
            end_ptr_index--;
        } else {
            found_index.push_back(*start_ptr);
            found_index.push_back(*end_ptr);

            numbers.erase(numbers.begin() + end_ptr_index);// Remove the last index after every time found
            return found_index;
        }  
    }
    
    found_index.push_back(-1);
    found_index.push_back(-1);
    return found_index; 
}
#define TARGET 2
int main(){
    vector<int> found_index;
    vector<int> numbers = {1, 2, 3, 4, 5};

    while (numbers.size() > 2){// Loop until there are only 2 member left inside the vector
        found_index = twoSubtraction(numbers, TARGET);
        for (int i = 0; i < found_index.size(); i++){
            cout << found_index[i] << " ";
        }
        cout << endl;
    }
    if ( (numbers.size() == 2) && ( (numbers[1] - numbers[0]) == TARGET)){
        cout << numbers[1] << " " << numbers[0] << endl;
    }
}
```
**Result**
```
3 5
2 4
1 3
```
**Notes**: The condition for the above implementation is each number appears only 1 time.
# Three sum
Given an integer array nums, return all the triplets {nums[i], nums[j], nums[k]} such that nums[i] + nums[j] + nums[k] == target.

We perform that by making the problem to be two sum - two pointer: [three_sum.cpp](https://github.com/TranPhucVinh/C/blob/master/Algorithms/src/three_sum.cpp)

# Implementations
* [Get the middle member of the linked list by 1 time traversing](https://github.com/TranPhucVinh/C/blob/master/Data%20structure/Linked%20list/Singly%20linked%20list/Read.md#get-the-middle-member-of-the-linked-list-by-1-time-traversing)
* [Verify if a given linked list is a circular linked list](https://github.com/TranPhucVinh/C/tree/master/Data%20structure/Linked%20list/Circular%20linked%20list#verify-if-a-given-linked-list-is-a-circular-linked-list)
