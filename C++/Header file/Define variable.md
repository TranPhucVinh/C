### Define value in header file, without class

**header.h**
```cpp
#include <iostream>
#ifndef header_h
#define header_h
#define integerValue 190

using namespace std;

class Header
{
  public:
    void hello();
  private:
    int _number;
};
#endif

void helloworld();
int value = 18;
```
**main.cpp**
```cpp
#include <iostream>
#include "header.h"

using namespace std;

int main() {
    cout << value << endl; //18
    cout << integerValue << endl; //190
    return 0;
}
```

```
18
190
```

### Error when value defined in ``.cpp``

**header.h**

```c
#include <iostream>
#ifndef header_h
#define header_h

using namespace std;

void helloworld();
int value;

#endif
```
**header.cpp**
```c
#include "header.h"
using namespace std;

value = 16;

void helloworld(){
	cout << value << endl;
}
```

**main.cpp**

```c
main(){
	helloworld();
}
```

**Error**

```
header.cpp:4:1: error: 'value' does not name a type
 value = 16;
 ^
header.cpp: In function 'void helloworld()':
header.cpp:7:10: error: 'value' was not declared in this scope
  cout << value << endl;
          ^
```

### Problem solve with extern

**header.h**

```c
void helloworld();
extern int value;
```

**header.h** has export variable **value** for other ``.cpp`` file to use by **extern**.

**header.cpp**

```c
int value = 16; 

void helloworld(){
	cout << value << endl;
}
```

Note that, to use variable **int**, it must be ``int value = 16``, not ``value = 16``.

**main.cpp**

```c
main(){
	helloworld();
}
```
**Result**: ``16``

### Multiple use with extern variable

**header.h**

```c
#include <iostream>

using namespace std;

void helloworld();
void setupInt();
extern int value;
```

**header.cpp**

```c
#include "header.h"
using namespace std;

void helloworld(){
	int value = 18; //must be call int variable_name each time
	cout << value << endl;
}

void setupInt(){
	int value = 19; //must be call int variable_name each time
	cout << value << endl;
}
```

```c
main(){
	helloworld();
	setupInt();
}
```
**Result**
```
18
19
```
