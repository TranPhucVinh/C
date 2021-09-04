Four key system calls for performing file I/O:

```c
fd = open(pathname, flags, mode);
```
```c
numread = read(fd, buffer, count);
```
```c
numwritten = write(fd, buffer, count);
```
```c
status = close(fd);
```