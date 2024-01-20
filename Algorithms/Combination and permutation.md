# Combination: Find all possible combinations of r elements in a given array of size n

The idea is to start from first index (index = 0) in ``data[]``, one by one fix elements at this index and recur for remaining indexes. 

Let the input array be ``{1, 2, 3, 4, 5}`` and ``r=3``. We first fix 1 at index 0 in data[], then recur for remaining indexes, then we fix 2 at index 0 and recur. Finally, we fix 3 and recur for remaining indexes. When number of elements in ``data[]`` becomes equal to ``r`` (size of a combination), we print ``data[]``.

![](https://github.com/TranPhucVinh/C/blob/master/Environment/Images/combination.jpg)

Full source code: [combination.c](combination.c)

# Permutation

A permutation of a set is an arrangement of its members into a sequence or linear order, or if the set is already ordered, a rearrangement of its elements. The word "permutation" also refers to the act or process of changing the linear order of an ordered set.

# Permutation values

Given n integer numbers from 1 to n, the algorithm to find their permutation is:

For position 1, there are n ways of arrangement, i.e: putting number 1 to n

For position 2, which comes after position 1, i.e the arrangement on this position must be implemented after position 1 is arranged, will have n-1 ways of arrangement

For position 3, same as position 2, will have n-2 way of arrangement

And so on

So the permutation of n member (1->n integer numbers) is n!

With ``n! = n.(n-1)!`` this infers us to use [recursive](https://github.com/TranPhucVinh/C/blob/master/Introduction/Function/README.md#recursive-function) for the permutation implementation.

# Find all permutation 

Take 3 numbers {1, 2, 3} for example.

To find all of the permutation members, based on the algorithm to form its formula, we will start at position 1

At position 1, there are 3 ways to arrange them, which results in the arranged string:

* 1xx
* 2xx
* 3xx

i.e: For the given string "123" (to form the permutation of 1, 2, 3), we will need to take the loop to swap all the left index from that given string to the 1st index member

In "123", swap 1st to 1st for 1xx, e.g 123, 132

In "123", swap 2nd to 1st for 2xx, e.g 213, 231

in "123", swap 3rd to 1st for 3xx, e.g 321, 312

For 1xx, value "1" now is fixed and we need to arrange the 2 left positions. Same for 2xx and 3xx

For the 2 left positions of 1xx, we now move to the 2nd positon. Perform the steps with the loop analysed before for the 1st position (1xx, 2xx and 3xx), i.e fixed the 2nd position which the left values in the given string, i.e {2, 3} (as "1" is fixed now). This steps is identically to the ones for the 1st postion. So we use recursive for that.

So the function for permutation based on the analysis till now is:

```c
/*
    @cid: current ID
*/
void permute(char *str_arr, int cid)

{
    for (int i = cid; i < strlen(str_arr); i++){
        swap(str_arr, i, cid);
        permute(str_arr, cid+1);
    }
}
```
For permutation implementation to get back to the original string after permute() has listed out all permutation of a fixed postion, e.g continue to list out all 2xx after 1xx is finished, swap() to get back to the orignal string need to be called after permute(str_arr, cid+1) is finished. So the for loop will be:
```c
for (int i = cid; i < strlen(str_arr); i++){
        swap(str_arr, i, cid);
        permute(str_arr, cid+1);
        swap(str_arr, i, cid);//Swap to switch back to the original string
}
```

For ``1xx``, the process to list out all permutation will end when the index cid reach the end of the given string array.

So the condition to stop the recursive call for a fixed positon like 1xx will be:

```c
if (cid == strlen(str_arr) - 1)
{
    member += 1;
    printf("%s\n", str_arr);
    return;
}
```

Full source code [permutation.c](permutation.c)
