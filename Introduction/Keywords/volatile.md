### Fundamental concepts

The ``volatile`` keyword is intended to prevent the compiler from applying any optimizations on objects that can change in ways that cannot be determined by the compiler. Objects declared as volatile are omitted from optimization because their values can be changed by code outside the scope of current code at any time.

Volatile keyword is useful for:

* Memory-mapped peripheral registers
* Global variables modified by an interrupt service routine
* Global variables accessed by multiple tasks within a multi-threaded application

### Applications

* Changing the value of a local or global const variable by pointer and ``memset()``.
* Using a volatile boolean variable as a mutex key to implement with 2 tasks inside FreeRTOS task: ``Example 2`` in ``Mutex.md``
(``AVR-Arduino-framework/FreeRTOS/Semaphore``). Its corresponding example in ESP8266 RTOS and C multithread doesn't require ``volatile`` declaration.