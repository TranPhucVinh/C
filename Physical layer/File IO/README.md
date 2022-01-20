# Fundamental concepts

## System call

Four key system calls for performing file manipulations:

```c
fd = open(pathname, flags, mode);//defined in fcntl.h
```
```c
numread = read(fd, buffer, count);//defined in unistd.h
```
```c
numwritten = write(fd, buffer, count);//defined in unistd.h
```
```c
status = close(fd);//defined in unistd.h
```

## Documents for IO types

* [stdio](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/File%20IO/stdio)
* [unistd](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/File%20IO/unistd.md)
* [fcntl](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/fcntl)
