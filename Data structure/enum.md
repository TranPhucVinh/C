# Define an enum

```c
enum {value0 = 10, value1, value2, value3, value4 = 10, value5 = 16, value6};
enum {value7, value8, value9, value10, value11=1, value12=12, value13};

printf("%d, %d, %d, %d, %d, %d, %d\n", value0 , value1, value2, value3, value4, value5, value6);//10, 11, 12, 13, 10, 16, 17
printf("%d, %d, %d, %d, %d, %d, %d\n", value7 , value8, value9, value10, value11, value12, value13);//0, 1, 2, 3, 1, 12, 13
```

**Notice**: After declaring the ``enum``, all variable inside ``enum`` (``value0``, ``value1``, ...) are all constant and unique.

# object of enum

```c
enum enum_object {value0 = 10, value1, value2, value3, value4 = 10, value5 = 16, value6};
enum enum_object enum_object_1;

printf("%d\n", enum_object_1);//0; enum_object_1 value now is not set
enum_object_1 = value0;
printf("%d\n", enum_object_1);//10
enum_object_1 = value1;
printf("%d\n", enum_object_1);//11
```

# enum as function parameter

Use ``typedef`` to set enum as function parameter:

```c
#include <stdio.h>

enum enum_object {value0 = 10, value1, value2, value3, value4 = 10, value5 = 16, value6};

typedef enum_object enum_object;

void callback_function(enum_object enum_object_1){
    printf("%d\n", enum_object_1);
}

int main(){
    enum_object enum_object_1 = value1;
    callback_function(enum_object_1);//11
}
```
# enum can be called from header file (without [ODR](../Introduction/Header/README.md#one-definition-rule-odr) issue)

``head.h``
```c
#include <stdio.h>

enum {value0 = 10, value1, value2, value3, value4 = 10, value5 = 16, value6};
```
``head.c``
```c
#include "head.h"
```
```c
#include "head.h"

int main() 
{ 
	printf("%d, %d, %d, %d, %d, %d, %d\n", value0 , value1, value2, value3, value4, value5, value6);//10, 11, 12, 13, 10, 16, 17
    return 0; 
} 
```
