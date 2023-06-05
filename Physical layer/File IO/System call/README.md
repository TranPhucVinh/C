# Fundamental concepts

Four key system calls for performing file manipulations:

```c
int fd = open(pathname, flags, mode);//defined in fcntl.h

ssize_t numread = read(fd, buffer, count);//defined in unistd.h

ssize_t numwritten = write(fd, buffer, count);//defined in unistd.h

int status = close(fd);//defined in unistd.h
```
The file I/O system calls refer to open files using a file descriptor.

As can be seen from the 4 key system calls, a file descriptor is typically obtained by a call to ``open()``, which takes a pathname argument specifying a file upon which I/O is to be performed.

Normally, a process inherits three open file descriptors when it is started by the shell (defined in ``stdio.h`` on Windows and in ``unistd.h`` on Unix)

```c
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */
```

## Header files

* ``fcntl.h``: file control options
* ``unistd.h`` provides access to the POSIX OS API.

# API

* [fcntl.h header files API](fcntl.md)
* [unistd.h header files API](unistd.md)

## termios.h

```c
#include <termios.h>

int tcgetattr(int fildes, struct termios *termios_p);
```

``tcsetattr``: set the parameters associated with the terminal

```c
#include <termios.h>

int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p);
```

The ``tcsetattr()`` function shall set the parameters associated with the terminal referred to by the open file descriptor ``fildes`` (an open file descriptor associated with a terminal) from the ``termios`` structure referenced by ``termios_p`` as follows:

* If ``optional_actions`` is ``TCSANOW``, the change shall occur immediately.
* If ``optional_actions`` is ``TCSADRAIN``, the change shall occur after all output written to ``fildes`` is transmitted. This function should be used when changing parameters that affect output.
* If ``optional_actions`` is ``TCSAFLUSH``, the change shall occur after all output written to ``fildes`` is transmitted, and all input so far received but not read shall be discarded before the change is made.

## I/O multiplexing API

I/O multiplexing API includes:

* [select()](select.md)
* [poll()](poll)
* [epoll](epoll)

# Examples

## [File operations](File%20operations.md)

* [Open a file to read](File%20operations.md#open-a-file-to-read)
* [Read the whole file by chunk and dynamically store to a char pointer](File%20operations.md#read-the-whole-file-by-chunk-and-dynamically-store-to-a-char-pointer)
* [Open a file to write](File%20operations.md#open-a-file-to-write)

## [Device file operations](Device%20file%20operations.md)

* Terminal operations: Read entered value from terminal and print out
* USB ports operations: Read data from USB port with default baudrate 9600 and other customized baudrate like 115200
* Read coordinate of a mouse cursor