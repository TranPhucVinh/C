### Fundamental concepts

Virtual memory is a section of volatile memory created temporarily on the storage drive. It is created when a computer is running many processes at once and RAM is running low.

Swapping is the process the OS uses to move data between RAM and virtual memory. The OS moves data from processes that are not immediately needed out of the RAM and stores them in virtual memory. It copies the data back into RAM when the process is needed again. Using virtual memory slows the computer down because copying to a hard disk takes much longer than reading and writing RAM.

### API

```c
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
```

``mmap()``: creates a new mapping in the virtual address space of the calling process. The starting address for the new mapping is specified in ``addr``.  The length argument specifies the length of the mapping (which must be greater than 0).

If ``addr`` is NULL, then the kernel chooses the (page-aligned) address at which to create the mapping; this is the most portable method of creating a new mapping.

The contents of a file mapping, are initialized using length bytes starting at ``offset``.

On success, ``mmap()`` returns a pointer to the mapped area.