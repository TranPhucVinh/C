# Fundamental concepts

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

**File descriptor**: The I/O system calls refer to open files using a file descriptor, a (usually small) non-negative integer. A file descriptor is typically obtained by a call to ``open()``, which takes a pathname argument specifying a file upon which I/O is to be performed.

Normally, a process inherits three open file descriptors when it is started by the shell:

```c
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */
```

## Header files

* ``fcntl.h``: file control options
* ``unistd.h`` provides access to the POSIX OS API.

# API

* [fcntl.h header files API](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call/fcntl.md)
* [unistd.h header files API](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call/unistd.md)

# Examples

[Examples](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call/Examples.md)