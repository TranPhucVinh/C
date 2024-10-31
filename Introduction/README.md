# [Function](#function)
## C doesn't support function overloading

C doesn't support function overloading as it is not an OOP language

For function overloading in [CPP](https://github.com/TranPhucVinh/Cplusplus), check [CPP function overloading document](https://github.com/TranPhucVinh/Cplusplus/tree/master/Introduction/Function#function-overloading).

## C doesn't support default arguments

Only CPP supports default arguments, check [CPP function for this implementation](https://github.com/TranPhucVinh/Cplusplus/tree/master/Introduction/Function#default-arguments).
# [Error handling](Error%20handling.md)

* C doesn't support try catch
* errno: EBUSY, EFAULT
* strerror()
# Get libc version

```c
#include <gnu/libc-version.h>
printf("%s\n", gnu_get_libc_version());
```
# [Unity unit test framework](Unit%20test.md)
## Stub function

A **stub** is a dummy or a testable replacement for a function or a variable.

**How to stub a function**: If there is a call to a function that handles a hardware functionality (for example a function to read temperature from a sensor), but this function is not testable in an offline environment like a standalone computer or in your local compiler, then you **STUB** it (or **REPLACE** it) with a dummy function, that does nothing or just increments a dummy variable, like ``x``.

So after you run you code, if you find that the variable ``x`` has been incremented, you know that the function (temperature sensor function) has been called.

For example, the temperature sensor function is ``Read_TempSens()``. We stub it with a dummy variable ``Test_ReadTemp`` as shown below

```c
int Test_ReadTemp;
#undef Read_TempSens()
#define Read_TempSens() Test_ReadTemp++
```
# Comparison to OOP

There are several cases where OOP with CPP must be implemented when comparing to their corresponding ones in C:

* [Stack building](../Data%20structure/Stack/README.md#build%20stack%20with%20array%20using%20struct)
* [Suspend and resume thread](../Physical%20layer/Thread/README.md#inter-task-communication)
