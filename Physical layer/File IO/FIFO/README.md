# Fundamental concepts

A **named pipe** (also known as a **FIFO** for its behavior) is an extension to the traditional pipe concept on Unix and Unix-like systems, and is used for data exchange between processes.

```c
#include <sys/types.h>
#include <sys/stat.h>

int mkfifo(const char *pathname, mode_t mode);
```
FIFO is a [half-duplex communication, not full-duplex, bidirection communication](Create%20a%20FIFO%20for%20RW.md#half-duplex-communication-with-fifo).
## mkfifo command

A FIFO can be created with ``mkfifo`` command:

``-m``, ``--mode=MODE``: File permission

E.g: 

``mkfifo -m 777 FIFO``: Create a FIFO named ``FIFO`` with mode ``777``.

After successfully creating, simply R/W to that FIFO by 2 process with normal ``read()``/``write()`` function.

# Implementations

[Create a FIFO for RW](Create%20a%20FIFO%20for%20RW.md): Fundamental implementation with FIFO

## IPC by FIFO

* [Process fifo_write writes data to FIFO every 1 second. Process fifo_read reads data from FIFO every 1 second](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/FIFO/IPC%20by%20FIFO.md)

## IPC by FIFO with scaling data method

Minimize float number to send as array member with 1 byte in the FIFO between 2 process with scaling factor ``65535`` [minimize_float_number_fifo_write.c](minimize_float_number_fifo_write.c) and [minimize_float_number_fifo_read.c](minimize_float_number_fifo_read.c).

**Result**

``./fifo_write``

```
Tranmit value: 15.82
Tranmit value: 59.96
Tranmit value: 21.47
Tranmit value: 19.95
Tranmit value: 8.75
```

``./fifo_read``

```
Received: 15.80
Received: 59.87
Received: 21.44
Received: 19.92
Received: 8.73
```
The received value in FIFO read different a little from FIFO write.

With scaling factor ``70000``:

``./fifo_write``
```
Tranmit value: 15.82
Tranmit value: 59.96
Tranmit value: 21.47
Tranmit value: 19.95
Tranmit value: 8.75
Tranmit value: 79.44
```

``./fifo_read``

```
Received: 15.82
Received: 59.95
Received: 21.47
Received: 19.95
Received: 8.75
Received: 79.43
```

However, if using big scaling factor ``100000``, the overflow issue might happen which lead to wrong conversion value in receiver side.  

``./fifo_write``

```
Tranmit value: 15.82
Tranmit value: 59.96
Tranmit value: 21.47
Tranmit value: 19.95
Tranmit value: 8.75
Tranmit value: 79.44 (overflow value)
Tranmit value: 65.81 (overflow value)
Tranmit value: 22.95
```

``./fifo_read``

```
Received: 15.82
Received: 59.95
Received: 21.47
Received: 19.95
Received: 8.75
Received: 14.55 (received wrong value)
Received: 0.93 (received wrong value)
Received: 22.94
```

