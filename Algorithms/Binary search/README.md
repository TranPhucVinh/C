# Fundamental concepts
Binary search is used to search for a specific member inside an ascending order array. This search method has the time complexity of O(log(n)) which is faster than the linear search method to iterate through every member of the array, which results in O(n).

Generally, binary search will chopping the half the array and search at the middle of it for every time searching, until it finds out the searched target.

For an ascending order array, binary search will search by searching at the middle of that array. If not match and:
* If array[middle] > target, it will start search at the middle of the 1/2 part of the array, starting from index 0 to index middle/2.
* If array[middle] <> target, it will start search at the middle of the 1/2 part of the array, starting from index middle/2 to the last index of the array.

# Fundamental concepts implementations
* [Implement by recursive]()
* [Implement by looping]()
* Count total occurence of a number inside a sorted array: Find index of the [1st occurrence](), [last occurenece]() of a number inside a sorted array
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
```c
int find_sqrt(int target, long start_index, long end_index) {
    long long middle = 0;
    if (start_index == end_index) {
        return start_index-1;
    }
    middle = (start_index + end_index)/2;// Middle index
    if (middle*middle == target) {
        return middle;
    }
    else if (target > middle*middle){
        return find_sqrt(target, middle+1, end_index);
    } else {
        return find_sqrt(target, start_index, middle);
    }
    
    return 0;
}

int mySqrt(int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;
    
    return find_sqrt(x, 1, x);
}
```