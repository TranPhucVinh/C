# Algorithms

There are 3 types of algorithms:
* Sorting algorithms
* Searching algorithms
* Graph algorithms

Algorithm complexity includes:
* **Time complexity**: The amount of time an algorithm takes to produce a result as a function of the size of the input
* **Space complexity** or memory complexity: The amount of memory used by an algorithm

The most most efficient and scalable alogorithm is the one with both lowest time and space complexity.

# Binary search

**Question**: What is the meaning/application of the DFS output in binary search as this output doesn't seem to give any information to state which path is traversed to get this output ? When investigating the DFS output, which information does it provide us ?

**Answer**: Searching data in a raw database (i.e database stored without any arrangement/ordered by a specific key) is inefficient. For efficient searching, database arrangement from the raw one is required.
A suggestion for that can be:

Raw database -> Specific key increment/decrement database (achieved by sorting algorithm) -> traversal table outputted by binary search.

We finally use that traversal table for searching, which will result in efficient search compared to raw database searching.

# [Big O](Big%20O)

# Beginner level

[Beginner level algorithm examples include](Beginner%20level.md):

* [Draw square with dots](Beginner%20level.md#draw-square-with-dots)
* [Find min number in an array](Beginner%20level.md#find-min-number-in-an-array)
* [Find prime number](Beginner%20level.md#find-prime-number)
* [Sum from 1 to n](#sum-from-1-to-n)
* [Reverse number](Beginner%20level.md#reverse-number)
* [Saddle point](saddle%point)
* [Expert system](Expert%20system)

## Sum from 1 to n

Features: Number ``n`` entered as ``main()`` argument

Handle error:

* Must enter 1 parameter for n, less than 1 or more than 1 parameter is not accepted.
* Accept value of ``n`` is integer ``2147483647``
* Negative number is not accepted
* Invalid number ``123abc`` is not accepted (for the parsing operation of ``atoi()``)

For the max accepted number of ``2147483647``, the result must be ``unsigned long int``, not ``int``.

Program: [sum_from_1_to_n.c](sum_from_1_to_n.c)

## Saddle point

Find [saddle point](https://github.com/TranPhucVinh/C/tree/master/Introduction/Data%20structure/Array#saddle-point) in a 2D array. Also check [saddle point document](https://github.com/TranPhucVinh/C/tree/master/Introduction/Data%20structure/Array#saddle-point) for the method to find saddle point inside a 2D array.

Program [saddle_point.c](saddle_point.c)

# Medium level

* [Find if a given number is the sum of consecutive numbers](https://github.com/TranPhucVinh/C/blob/master/Algorithms/Medium%20level.md#find-if-a-given-number-is-the-sum-of-consecutive-numbers)
* [Find the nth digit of an infinite integer sequence](https://github.com/TranPhucVinh/C/blob/master/Algorithms/Medium%20level.md#find-the-nth-digit-of-an-infinite-integer-sequence)

# [Permutation](Permutation.md), [combination](Combination.md)

# Sorting algorithms

* [Selection sort](Sorting%20algorithms#selection-sort)
* [Bubble sort](Sorting%20algorithms#bubble-sort)
