# Selection sort 

The selection sort algorithm sorts an array by repeatedly finding the minimum element (considering ascending order) from unsorted part and putting it at the beginning. The algorithm maintains two subarrays in a given array:

* The subarray which is already sorted. 
* Remaining subarray which is unsorted.

In every iteration of selection sort, the minimum element (considering ascending order) from the unsorted subarray is picked and moved to the sorted subarray. 

**Implementation**: [selection_sort.c](selection_sort.c)

# Bubble sort 

Bubble Sort works by repeatedly swapping the adjacent elements if they are in the wrong order.

**First pass**

Bubble sort starts with very first two elements, comparing them to check which one is greater.

(``5`` ``1`` 4 2 8) –> (``1`` ``5`` 4 2 8 ): Here, algorithm compares the first two elements, and swaps since 5 > 1. 

(1 ``5`` ``4`` 2 8) –> (1 ``4`` ``5`` 2 8): Swap since 5 > 4 

(1 4 ``5`` ``2`` 8) –> (1 4 ``2`` ``5`` 8), Swap since 5 > 2 

(1 4 2 ``5`` ``8``) –> (1 4 2 ``5`` ``8``), Now, since these elements are already in order (8 > 5), algorithm does not swap them.

**Second pass**

Now, during second iteration it should look like this:

(1 4 2 5 8) –> ( 1 4 2 5 8) 

(1 ``4`` ``2`` 5 8) –> ( 1 ``2`` ``4`` 5 8 ), swap since 4 > 2 

(1 2 4 5 8) –> (1 2 4 5 8) 

(1 2 4 5 8) –>  (1 2 4 5 8) 

**Third pass**

Now, the array is already sorted, but our algorithm does not know if it is completed.

The algorithm needs one whole pass without any swap to know it is sorted.

(1 2 4 5 8) –> ( 1 2 4 5 8) 

(1 2 4 5 8) –> ( 1 2 4 5 8) 

(1 2 4 5 8) –> ( 1 2 4 5 8) 

(1 2 4 5 8) –> ( 1 2 4 5 8) 

**Implementation**: [bubble_sort.c](bubble_sort.c)
