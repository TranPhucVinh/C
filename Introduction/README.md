# [Function](#function)
[Fundamental concepts](Function/Fundamental%20concepts.md):
* Create the very first function
* Function with arguments: Function prototype, function arguments as void
* Short term function data type
* return keyword
* Command line arguments with main()

[Other concepts](Function/Other%20concepts.md):
* [Callback function](Callback%20function.md)
* [Variadic function and variable length argument](Variadic%20function.md)
* [Scope](Scope.md)
* [Random number generators](Random%20number.md)
* C doesn't support function overloading
* C doesn't support default arguments
# [Error handling](Error%20handling.md)

* C doesn't support try catch
* errno: EBUSY, EFAULT
* strerror()

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
