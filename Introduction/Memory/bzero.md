### bzero()

```c
void bzero(void *s, size_t n);
```

The **bzero()** function shall place n **zero-valued bytes** in the area pointed to by s.

The **bzero()** function copies n bytes, each with a value of zero, into string s.

``s``: Points to a buffer that zeros are copied into.

``n``: Is the number of zeros to be copied into the buffer.

**Example**

```c
int main() {
    int hello[] = {1, 2, 3}, i;
    size_t arraySize = sizeof(hello)/sizeof(hello[0]);
    printf("before ");
    for(i=0; i<arraySize; i++){
    	printf("%d: %d \n", i, hello[i]);
    }
    bzero(hello, 1);
    printf("after ");
    for(i=0; i<arraySize; i++){
    	printf("%d: %d \n", i, hello[i]);
    }
    return 0;
}
```

```
before 0: 1 
1: 2 
2: 3 
after 0: 0 
1: 2 
2: 3 
```

Because an int value has 4-byte, so to set other int value in array to 0, it has to increase the value to every 4 byte for a member in array.

```c
int hello[] = {1, 4, 4, 6, 789}, i;
bzero(hello, 8);
    printf("after ");
    for(i=0; i<arraySize; i++){
    	printf("%d: %d \n", i, hello[i]);
    }
```    

```
after 0: 0 
1: 0 
2: 4 
3: 6 
4: 789 
```

Set all value to 0 in array

```c
bzero(hello, sizeof(hello));
```

### With char

```c
int main() {
    int i;
    char hello[] = "a character";
    bzero(hello, 1);
    printf("after ");
    printf("%s \n", hello);
    return 0;
}
```

```
after  (empty)
```