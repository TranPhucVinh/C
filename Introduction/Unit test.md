[Unity](https://github.com/ThrowTheSwitch/Unity) is a C unit test framework.

Download Unity zip file or clone the Unity Github then include the Unity source path while running

```
working_folder
|--Unity
   |--src
      |--unity.c
      |--unity.h
      |-- Other source files
|--main.c
```

Where 
* ``Unity`` is the Unity source folder, downloaded/cloned before
* ``main.c``: Source code to run unit test

``main.c``

```c
#include "unity.h"

void test_assert(void)
{
    int a = 1;
    TEST_ASSERT(a == 1);
    TEST_ASSERT_EQUAL_INT(4, 3+1);
}

void setUp(){
    return;
}

void tearDown(){
    return;
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_assert);
    return UNITY_END();
}
```
**Compile**: ``gcc main.c Unity/src/unity.c -IUnity/src``

**Result**: 

```
main.c:21:test_assert:PASS

-----------------------
1 Tests 0 Failures 0 Ignored
OK
```
