# Virtual memory
User space applications are not allowed to access peripheral registers, storage media or even RAM memory directly. Instead, the hardware is accessed via  kernel drivers, and RAM memory is managed by the memory management unit (MMU), with user space applications operating on **virtual addresses**.

**Virtual memory** is a section of volatile memory created temporarily on the storage drive. It is created when a computer is running many processes at once and RAM is running low.

The OS’s process abstraction provides each process with a virtual memory space so address of a variable inside a process is virtual address.

Because processes operate within their own virtual address spaces, operating systems must make an important distinction between two types of memory addresses.
Virtual addresses refer to storage locations in a process’s virtual address space, and physical addresses refer to storage locations in physical memory (RAM).

Swapping is the process the OS uses to move data between RAM and virtual memory. The OS moves data from processes that are not immediately needed out of the RAM and stores them in virtual memory. It copies the data back into RAM when the process is needed again. Using virtual memory slows the computer down because copying to a hard disk takes much longer than reading and writing RAM.

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
