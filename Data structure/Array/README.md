An array is collection of items stored at **continuous memory** locations.

# [One dimension array](One%20dimension%20array.md)

* [Create](One%20dimension%20array.md#create): [Create an array on stack memory](One%20dimension%20array.md#on-stack-memory) and [on heap memory](); [create/insert new member at specific index](create_new_member.c); [create a vector](create_vector.c)
* [Read](One%20dimension%20array.md#read)
* [Update](One%20dimension%20array.md#update)
* [Delete](One%20dimension%20array.md#delete): [Delete member in array from index](delete.c)

# [One dimension array and function](One%20dimension%20array%20and%20function.md)
* [Array as an argument of a function](One%20dimension%20array%20and%20function.md#array-as-an-argument-of-a-function): [using array with size]() and [using array pointer]()
* [Function returns an array](): [Using stack memory with static]() and [Using heap memory with malloc()]()

# Multidimension array

GCC treats multidimension array as one dimension array.

```c
int array[3][3]={1, 2, 3, 4, 5, 6, 7, 8}
```

``array[3][3]`` can defined as ``array[][3]``. ``array[][3]`` infers that there are 3 columns. The missing value in each group is set to ``0``. So ``array[][3]`` is then treated as:

```c
int array[][3] ={
 	{1,2,3},
	{4,5,6},
	{7,8}};
```

The interpreted of ``array[][3]`` in this case is **unique**.

Define ``array[3][]`` is wrong and gives compilation error, as this array can't tell how many columns it has. The interpreted of ``array[3][]`` in this case is **not unique** as it now can be understand as:

```c
{{1,2},{3,4},{5,6,7,8}}
{{1,2,3},{4},{5,6,7,8}}
{{1,2,3,4},{5,6,7,8}}
...//Not unique, must not define: int array[3][]
```

## An equivalent pointer expression for referring the same element a[i][j][k][l]

We know that ``a[i]`` can be written as ``*(a+i)``. Same way, the array elements can be written like pointer expression as follows:

```c
a[i][j] = *(*(a+i)+j);
a[i][j][k] = *(*(*(a+i)+j)+k);
a[i][j][k][l] = *(*(*(*(a+i)+j)+k)+l);
```

# Two dimension array implementations
* [Two dimension array on stack memory](Two%20dimension%20array%20on%20stack%20memory.md)
* [Two dimension array on heap memory](Two%20dimension%20array%20on%20heap%20memory.md)

# Matrix
## Main diagonal and antidiagonal 
* The main diagonal of a matrix is the list of entries a[i][j] such that i = j
* The antidiagonal, which only **available inside a square matrix** of size N, is the list of entries a[i][j] such that i+j = N-1

## Saddle point

In a square matrix with n * n size, a saddle point is an element of the matrix such that it is the minimum element in its row and the maximum in its column. 

**The algorithm to find the saddle point**

Traverse all rows one by one and do the following for every row ``i``:  

1. Find the minimum element of the current row and store the column index of the minimum element.
2. Check if the row minimum element is also maximum in its column. We use the stored column index here.
3. If yes, then saddle point else continues till the end of the matrix.

Program [saddle_point.c](https://github.com/TranPhucVinh/C/blob/master/Algorithms/saddle_point.c)
# [Algorithm problem with array](https://github.com/TranPhucVinh/C/tree/master/Algorithms/Array)
* Find min number in an array
* Saddle point
* Sort an array into **ascending** or **descending** order: Refer to [Sorting algorithms](https://github.com/TranPhucVinh/C/tree/master/Algorithms/Sorting%20algorithms#selection-sort)
