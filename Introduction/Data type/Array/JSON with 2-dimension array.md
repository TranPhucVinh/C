### 2-dimension array

JSON

```cpp
#include <stdio.h>

char ch_arr[3][10] = {
                         "spike",
                         "tom",
                         "jerry"
                     };

main() {
	for (int i=0; i < 3; i++){
		printf("string: %s \n", ch_arr + i);
	}
}
```

**Result**

```
string: spike 
string: tom 
string: jerry 
```