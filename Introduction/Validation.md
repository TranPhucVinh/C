# Unit test with Unity
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
# Stub function

A **stub** is a dummy or a testable replacement for a function or a variable.

**How to stub a function**: If there is a call to a function that handles a hardware functionality (for example a function to read temperature from a sensor), but this function is not testable in an offline environment like a standalone computer or in your local compiler, then you **STUB** it (or **REPLACE** it) with a dummy function, that does nothing or just increments a dummy variable, like ``x``.

So after you run you code, if you find that the variable ``x`` has been incremented, you know that the function (temperature sensor function) has been called.

For example, the temperature sensor function is ``Read_TempSens()``. We stub it with a dummy variable ``Test_ReadTemp`` as shown below

```c
int Test_ReadTemp;
#undef Read_TempSens()
#define Read_TempSens() Test_ReadTemp++
```