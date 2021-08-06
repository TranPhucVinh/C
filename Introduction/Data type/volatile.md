### Applications

* Changing the value of a local or global const variable by pointer and ``memset()``.
* Using a volatile boolean variable as a mutex key to implement with 2 tasks inside FreeRTOS task: ``Example 2`` in ``Mutex.md``
(``AVR-Arduino-framework/FreeRTOS/Semaphore``). Its corresponding example in ESP8266 RTOS and C multithread doesn't require ``volatile`` declaration.