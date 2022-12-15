## open()

Open file/stream or possibly create a file

```c
int fd = int open(const char *path, int mode)
```

``path``: path of file or stream (like ``stdin``, ``stdout``, ``stderr``,...)

``mode``:

* ``O_CREAT``: Create a file if not existed. If file is already existed, open that file successfully with a valid fd returned.
* ``O_RDONLY``: READ ONLY
* ``O_WRONLY``: WRITE ONLY
* ``O_RDWR``: READ and WRITE
* ``O_APPEND``: APPEND to WRITE
* ``O_NONBLOCK``: Prevents open() from blocking for a “long time” to open the file. This is only meaningful for some kinds of files like ``FIFO``, ``block file``, ``character device file``, and serial ports.
* ``O_EXCL``: ``O_EXCL`` must go with ``O_CREAT`` with ``|`` operator to detect the error when trying to create (with ``O_CREAT``flag ) an existed file.

**Return**: ``fd`` if file successfully opened or ``-1`` if error open, e.g: file not exist when opening with mode ``O_RDONLY``

``O_EXCL`` example: 

```c
int fileDescription = open(FILE_NAME, O_CREAT|O_EXCL);
printf("%d\n", errno);
```

Run this program for the first time, ``errno`` is ``0`` as there is no errno and the file ``FILE_NAME`` is created.

Run this program for the second time, ``errno`` is ``EEXIST 17 File exists`` as the file ``FILE_NAME`` has already been created.
## creat()

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