An array is collection of items stored at **continuous memory** locations.

# [One dimension array](One%20dimension%20array)

* [Create](One%20dimension%20array/Create.md): 
* [Read](One%20dimension%20array/Read.md)
* [Update](One%20dimension%20array.md#update)
* [Delete](One%20dimension%20array.md#delete): [Delete member in array from index](delete.c)

# [One dimension array and function](One%20dimension%20array%20and%20function.md)
* [Array as an argument of a function](One%20dimension%20array%20and%20function.md#array-as-an-argument-of-a-function): [using array with size]() and [using array pointer]()
* [Function returns an array](): [Using stack memory with static]() and [Using heap memory with malloc()]()

# [Multidimension array](Multidimension%20array)

# Matrix
## Main diagonal and antidiagonal 
* The main diagonal of a matrix is the list of entries a[i][j] such that i = j
* The antidiagonal, which only **available inside a square matrix** of size N, is the list of entries a[i][j] such that i+j = N-1 where 0 <= i, j < N

## Saddle point

In a square matrix with n * n size, a saddle point is an element of the matrix such that it is the minimum element in its row and the maximum in its column. 

**The algorithm to find the saddle point**

Traverse all rows one by one and do the following for every row ``i``:  

1. Find the minimum element of the current row and store the column index of the minimum element.
2. Check if the row minimum element is also maximum in its column. We use the stored column index here.
3. If yes, then saddle point else continues till the end of the matrix.

Program [saddle_point.c](https://github.com/TranPhucVinh/C/blob/master/Algorithms/saddle_point.c)
