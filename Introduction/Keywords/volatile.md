# Fundamental concepts

The ``volatile`` keyword is intended to prevent the compiler from applying any optimizations on objects that can change in ways that cannot be determined by the compiler. Objects declared as volatile are omitted from optimization because their values can be changed by code outside the scope of current code at any time.

Volatile keyword is useful for:

* Memory-mapped peripheral registers
* Global variables modified by an interrupt service routine
* Global variables accessed by multiple tasks within a multi-threaded application

# Applications

* [Changing the value of a local or global const variable by pointer](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Pointer/Implementations.md#change-value-of-a-variable-with-pointer) and [memset()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/API/memset.md#change-const-variable-with-memeset).
* [Using a simple boolean variable as a mutex key to implement with 2 tasks in AVR Arduino FreeRTOS](https://github.com/TranPhucVinh/AVR-Arduino-framework/blob/master/FreeRTOS/Inter-task%20communication/Mutex.md#using-a-simple-boolean-variable-as-a-mutex-key-to-implement-with-2-tasks). Its corresponding example in ESP8266 RTOS and C multithread doesn't require ``volatile`` declaration.
* ``overflowFlag`` variable in [Automatic filling machine AVR Arduino project](https://github.com/TranPhucVinh/AVR-Arduino-framework/tree/master/Projects/Automatic%20filling%20machine) is ``volatile``.
