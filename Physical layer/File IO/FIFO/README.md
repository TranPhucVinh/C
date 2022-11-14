# Fundamental concepts

A named pipe (also known as a **FIFO** for its behavior) is an extension to the traditional pipe concept on Unix and Unix-like systems, and is one of the methods of inter-process communication (IPC).

```c
#include <sys/types.h>
#include <sys/stat.h>

int mkfifo(const char *pathname, mode_t mode);
```

## mkfifo command

A FIFO can be created with ``mkfifo`` command:

``-m``, ``--mode=MODE``: File permission

E.g: 

``mkfifo -m 777 FIFO``: Create a FIFO named ``FIFO`` with mode ``777``.

After successfully creating, simply R/W to that FIFO by 2 process with normal ``read()``/``write()`` function.

# Examples

Check [examples document](Examples.md)
