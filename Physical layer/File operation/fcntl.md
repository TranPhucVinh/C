``fcntl.h``: file control options

### open()

Open file/stream

``int fileDescriptor = int open(const char *path, int mode)``

* path: path of file or stream (like ``stdin``, ``stdout``, ``stderr``,...)
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

### File descriptor

```c
const char filePath[] = "test.txt";
fileDescriptor = open(filePath, O_WRONLY);
```

If this ``open()`` line of code is run the first time inside the source code and ``test.txt`` exists, then ``fileDescription`` is ``3``.

``0``, ``1`` and ``2`` are file descriptor value of ``stdin``, ``stdout`` and ``stderr``

However, ``open("/dev/stdin", O_RDONLY)`` returns ``3``.

Everytime any file open (the same file or not), ``fileDescriptor`` will increase by ``1``.

```c
char filePath[] = "test.txt";
fileDescription = open(filePath, O_RDONLY);//Open test.txt
printf("%d", fileDescription);//3
fileDescription = open(filePath, O_RDONLY);//Open test.txt again
printf("%d", fileDescription);//4
```