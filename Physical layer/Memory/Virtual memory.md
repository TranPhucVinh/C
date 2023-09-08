# mmap()

```c
#include <sys/mman.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
```

``mmap()``: creates a new mapping in the virtual address space of the calling process. The starting address for the new mapping is specified in ``addr``.  The length argument specifies the length of the mapping (which must be greater than 0).

If ``addr`` is NULL, then the kernel chooses the (page-aligned) address at which to create the mapping; this is the most portable method of creating a new mapping.

The contents of a file mapping, are initialized using length bytes starting at ``offset``.

On success, ``mmap()`` returns a pointer to the mapped area.

``prot``: memory protection of the mapping (and must not conflict with the open mode of the file).

*  ``PROT_EXEC``: Pages may be executed.
* ``PROT_READ``: Pages may be read.
* ``PROT_WRITE``: Pages may be written.
* ``PROT_NONE``: Pages may not be accessed.

``flags``:

* ``MAP_SHARED``: Share this mapping for usage in [shared memory](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process/Shared%20memory)
* ``MAP_PRIVATE``: Create a private copy-on-write mapping
* ``MAP_ANONYMOUS``: The mapping doesn't involve any file descriptor (i.e parameter ``fd =-1``)

# Virtual memory implementation by mmap()

* [Read the value stored in Raspberry Pi physical address 0x3f20000](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Physical%20layer/Direct%20register%20access.md#mmap)

* [Control GPIO of Raspberry Pi by direct memory access using mmap()](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Physical%20layer/GPIO/direct_register_access_control_gpio.c), notice that ``addr`` param in ``mmap()`` is ``NULL`` in this case.
