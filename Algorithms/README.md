# Overview of algorithms

There are 3 types of algorithms:
* Sorting algorithms
* Searching algorithms
* Graph algorithms

Algorithm complexity includes:
* **Time complexity**: The amount of time an algorithm takes to produce a result as a function of the size of the input
* **Space complexity** or memory complexity: The amount of memory used by an algorithm

The most most efficient and scalable alogorithm is the one with both lowest time and space complexity.

# [Big O](Big%20O)

# [Array](Array)
* [Find min number in an array](Beginner%20level.md#find-min-number-in-an-array)
* [Saddle point](saddle%point)
# String
* [Convert a valid Roman numerals to integer, using map](https://github.com/TranPhucVinh/Cplusplus/blob/master/Data%20structure/src/map_roman_numerals_to_integer.cpp)
* [Convert an integer to Roman numeral by using vector tuple](https://github.com/TranPhucVinh/Cplusplus/blob/master/Data%20structure/src/vector_tuple_integer_to_roman_numeral.cpp)
# [Sequence](Sequence.md)

Sequence or **sequence of numbers** problem include:
* [Sum from 1 to n](#sum-from-1-to-n)
* [Find if a given number is the sum of consecutive numbers](https://github.com/TranPhucVinh/C/blob/master/Algorithms/Medium%20level.md#find-if-a-given-number-is-the-sum-of-consecutive-numbers)
* [Find the nth digit of an infinite integer sequence](https://github.com/TranPhucVinh/C/blob/master/Algorithms/Medium%20level.md#find-the-nth-digit-of-an-infinite-integer-sequence)
## Sum from 1 to n

Features: Number ``n`` entered as ``main()`` argument

Handle error:

* Must enter 1 parameter for n, less than 1 or more than 1 parameter is not accepted.
* Accept value of ``n`` is integer ``2147483647``
* Negative number is not accepted
* Invalid number ``123abc`` is not accepted (for the parsing operation of ``atoi()``)

For the max accepted number of ``2147483647``, the result must be ``unsigned long int``, not ``int``.

Program: [sum_from_1_to_n.c](sum_from_1_to_n.c)
# [Permutation](Permutation.md), [combination](Combination.md)

# Binary search

**Question**: What is the meaning/application of the DFS output in binary search as this output doesn't seem to give any information to state which path is traversed to get this output ? When investigating the DFS output, which information does it provide us ?

**Answer**: Searching data in a raw database (i.e database stored without any arrangement/ordered by a specific key) is inefficient. For efficient searching, database arrangement from the raw one is required.
A suggestion for that can be:

Raw database -> Specific key increment/decrement database (achieved by sorting algorithm) -> traversal table outputted by binary search.

We finally use that traversal table for searching, which will result in efficient search compared to raw database searching.

# Sorting algorithms

* [Selection sort](Sorting%20algorithms#selection-sort)
* [Bubble sort](Sorting%20algorithms#bubble-sort)

# Algorithm for database

A recommended solution for building a database, along with **displaying** and **searching**, in C/PP is
* **Display**: Store the data of each employee in a specific file format like JSON, dictionary. The display operation will then read all those files to display in the column
* **Search**: Arrange the data into a descending or ascending order then perform a search method, e.g binary search. Also refer to the [binary search result for its application](https://github.com/TranPhucVinh/C/blob/master/Algorithms/README.md#binary-search)

It's a **bad practice** to use a file as a database to store all information, e.g device information, then this file is opened for appending at its end of it (for adding new database member) or searching at each line of the file (for search operation). This generally results in high time complexity.
