# Header file

To compile with mupltiples header files

``g++ -o outputFile main.c other.c etc.c``

``g++ -o outputFile main.cpp other.cpp etc.cpp``

## Basic header file

### In C

**Define function, variable in ``.h`` file.**

``head.h``

```c
#include <stdio.h>

void helloworld(){
	printf("Hello World \n");
}

int value = 6;
```

``main.c``

```c
#include "head.h"

int main(){
	helloworld(); //Hello World
	printf("%d \n", value); //6
}
```

**Define function, variable in ``.c`` file.**

``head.h``

```cpp
#include <stdio.h>

void helloworld();
```

``head.c``

```cpp
#include "head.h"

void helloworld(){
    printf("Hello World \n");
}
```

``main.c``

```c
#include "head.h"

int main(){
	helloworld(); //Hello World
}
```

### In CPP

``header.h``

```cpp
#include <iostream>
using namespace std; // this line is optional

void helloworld();
```

``header.cpp``

```cpp
#include <iostream>
#include "header.h"
using namespace std; // this line is optional

void helloworld(){
	cout << "Hello, World!" << endl;
}
```

``main.cpp``

```cpp
#include <iostream>
#include "header.h" //"header.h", not <header.h>

using namespace std;

int main(){
	helloworld(); //Hello, World!
}
```