# Binary search

**Question**: What is the meaning/application of the DFS output in binary search as this output doesn't seem to give any information to state which path is traversed to get this output ? When investigating the DFS output, which information does it provide us ?

**Answer**: Searching data in a raw database (i.e database stored without any arrangement/ordered by a specific key) is inefficient. For efficient searching, database arrangement from the raw one is required.
A suggestion for that can be:

Raw database -> Specific key increment/decrement database (achieved by sorting algorithm) -> traversal table outputted by binary search.

We finally use that traversal table for searching, which will result in efficient search compared to raw database searching.

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
