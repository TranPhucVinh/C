### API

```c
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
```

``mmap()``: creates a new mapping in the virtual address space of the calling process. The starting address for the new mapping is specified in ``addr``.  The length argument specifies the length of the mapping (which must be greater than 0).

If ``addr`` is NULL, then the kernel chooses the (page-aligned) address at which to create the mapping; this is the most portable method of creating a new mapping.

The contents of a file mapping, are initialized using length bytes starting at ``offset``.

On success, ``mmap()`` returns a pointer to the mapped area.
