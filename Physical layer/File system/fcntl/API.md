### open()

Open file/stream

``int fileDescription = int open(const char *path, int mode)``

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