**Error when value defined outside ``.h``**

``header.h``

```c
int a;
```

``header.c``

```c
#include <stdio.h>
#include "head.h"

a = 18;
```

```c
#include "head.h"

main(){
	printf("%d \n", a);
}
```

This will be an error

```
In file included from test.c:9:0:
head.c:5:2: error: ‘a’ does not name a type
  a = 18;
```

### Problem solve with extern

``header.h``

```c
void helloworld();
extern int value;
```

``header.h`` has exported variable ``value`` for other ``.cpp`` file to use by ``extern``.

``header.cpp``

```c
int value = 16; 

void helloworld(){
	cout << value << endl;
}
```

Note that, to use variable **int**, it must be ``int value = 16``, not ``value = 16``.

``main.cpp``

```c
main(){
	helloworld(); //16
}
```

### Multiple use with extern variable

Define variable with extern in 2 functions.

``header.h``

```cpp
#include <iostream>

using namespace std;

void helloworld();
void setupInt();
extern int value;
```

``header.cpp``

```cpp
#include "header.h"
using namespace std;

//define variable value in function helloworld
void helloworld(){
	int value = 18;
	cout << value << endl;
}

//define variable value in function setupInt
void setupInt(){
	int value = 19;
	cout << value << endl;
}
```

``main.cpp``

```c
#include "header.h"

main(){
	helloworld(); //18
	setupInt(); //19
}
```