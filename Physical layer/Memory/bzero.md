### bzero()

```c
void bzero(void *s, size_t n);
```

``bzero()`` function copies ``n`` bytes, each with a value of zero, into string ``s``

* ``s``: the buffer that zeros are copied into
* ``n``: the number of zeros to be copied into the buffer

``bzero()`` is not part of the standard library, it belongs to POSIX.

**Example**

```c
#include <stdio.h>
#include <string.h>

int main() {
    int array[] = {1, 2, 3};
    size_t arraySize = sizeof(array)/sizeof(array[0]);
    printf("before: ");
    for(int i=0; i<arraySize; i++){
    	printf("%d, ", array[i]);
    }
    bzero(array, 1);
    printf("\nafter: ");
    for(int i=0; i<arraySize; i++){
    	printf("%d, ", array[i]);
    }
    return 0;
}
```

```
before: 1, 2, 3, 
after: 0, 2, 3,
```

Because an int value has 4-byte, so to set others int value in array to 0, it has to increase the value to every 4 byte for a member in array.

For example:  ``bzero(array, 8)``

Result: ``after: 0, 0, 3,``


Set all value to 0 in array: ``bzero(hello, sizeof(hello))``

### Empty a string

```c
#include <stdio.h>
#include <string.h>

int main() {
    char displayedString[] = "a character";
	printf("before: %s \n", displayedString);
    bzero(displayedString, 1);
    printf("after: %s \n", displayedString);
    return 0;
}
```

```
before: a character 
after:  
```