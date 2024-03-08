# Binary search

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
