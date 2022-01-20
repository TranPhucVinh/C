``fcntl.h``: file control options

## API

### open()

Open file/stream

```c
int fileDescriptor = int open(const char *path, int mode)
```

* ``path``: path of file or stream (like ``stdin``, ``stdout``, ``stderr``,...)
* mode:

| Mode | Description|NOTE
| ------- |:------:|:--------:|
|O_RDONLY | READ ONLY|int = 0|
|O_WRONLY | WRITE ONLY|int = 1|
|O_RDWR| READ and WRITE|int = 2|
|O_APPEND|APPEND to WRITE|
|O_EXEC|Open for execution|
|O_SEARCH|Open for searching (for directory)|
|O_CLOEXEC| Open FD_CLOEXEC for file descriptor|
|O_CREAT | Create a file if not existed|
|O_DIRECTORY| Return error if path is not a directory|
|O_EXCL| Check for file existence|
|O_NOCTTY||
|O_NOFOLLOW| Return error if path is symbolic link|
|O_NONBLOCK| (1)|
|O_SYNC| Wait for hardware's synchronization every time read/write|
|O_TRUNC| Delete all file data if file existed and opened successfully|
|O_TTY_INIT| Used to open I/O device|

(1): If path is a ``FIFO``, ``block file`` or ``character special file``, ``O_NONBLOCK`` will open and read/write file without blocking

### creat()

```c
int fileDescriptor = int creat(const char * pathname , mode_t mode);
```
``mode_t`` takes octal value like ``0777`` for better mode clarification.

Calling ``creat()`` is equivalent to the following ``open()`` call:

```c
fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
```

Because the ``open()`` flags argument provides greater control over how the file is opened (e.g., we can specify ``O_RDWR`` instead of ``O_WRONLY``), ``creat()`` is now obsolete, although it may still be seen in older programs.

## File descriptor

```c
const char filePath[] = "test.txt";
fileDescriptor = open(filePath, O_WRONLY);
```

If this ``open()`` line of code is run the first time inside the source code and ``test.txt`` exists, then ``fileDescription`` is ``3``.

``0``, ``1`` and ``2`` are file descriptor value of ``stdin``, ``stdout`` and ``stderr``. In an interactive shell or program, these three descriptors are normally connected to the terminal.

However, ``open("/dev/stdin", O_RDONLY)`` and ``open("/dev/tty", O_RDONLY)`` return ``3``.

Everytime any file open (the same file or not), ``fileDescriptor`` will increase by ``1``.

```c
char filePath[] = "test.txt";
fileDescription = open(filePath, O_RDONLY);//Open test.txt
printf("%d", fileDescription);//3
fileDescription = open(filePath, O_RDONLY);//Open test.txt again
printf("%d", fileDescription);//4
```

Check error with ``errno`` of library ``errno.h``

```c
#include <errno.h>
int fileDescription = open(filePath, O_RDONLY);
printf("%d\n", errno);
```

If the file is exist and no error happen, ``errno`` is ``0``.

If the file is not exist, ``errno`` will be ``2`` (``ENOENT``).
