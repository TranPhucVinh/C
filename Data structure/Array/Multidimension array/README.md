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

# An equivalent pointer expression for referring the same element a[i][j][k][l]

We know that ``a[i]`` can be written as ``*(a+i)``. Same way, the array elements can be written like pointer expression as follows:

```c
a[i][j] = *(*(a+i)+j);
a[i][j][k] = *(*(*(a+i)+j)+k);
a[i][j][k][l] = *(*(*(*(a+i)+j)+k)+l);
```
# [Two dimension array on stack memory](Two%20dimension%20array%20on%20stack%20memory.md)
# [Two dimension array on heap memory](Two%20dimension%20array%20on%20heap%20memory.md)