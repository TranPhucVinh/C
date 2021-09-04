Four key system calls for performing file I/O:

```c
fd = open(pathname, flags, mode);
numread = read(fd, buffer, count);
numwritten = write(fd, buffer, count);
status = close(fd);
```