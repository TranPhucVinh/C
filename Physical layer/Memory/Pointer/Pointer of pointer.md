### Create

```c
int number1 = 9;

int *ptr = &number1;
int **pptr = &ptr;

int main(){
  printf("ptr: %p \n", ptr);
  printf("pptr: %p \n", pptr);
  printf("**pptr: %d \n", **pptr); //9
}
```

### Applications

* [Array of pointer](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/Array/Array%20of%20pointer.md)
* [Create a 2 dimension int array with malloc()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Dynamic%20memory/Using%20stdlib.md)
* [Thread creation: Get return from a thread and store to a variable](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Examples.md#example-1)
