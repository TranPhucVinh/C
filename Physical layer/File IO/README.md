# Fundamental concepts

* [stdio](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/File%20IO/stdio)
* [File I/O system call](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call)
* [pipe](pipe.md)
* [FIFO](FIFO)
* [stat](stat.md)
* [uio](uio)

# Read entered value from stream in

Method to read entered value from stream in with fix dynamic allocation size for the buffer to store the entered string/value:
* [scanf()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/stdin%20and%20stdout%20API.md#scanf) and [fgets()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/File%20pointer%20API.md#fgets)
* [read() system call with stdin file descriptor (STDIN_FILENO) to read the entered string in terminal](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call/Device%20file%20operations.md#terminal-operations)
* [gets() (deprecated) to read entered string](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/stdin%20and%20stdout%20API.md#gets-and-puts), [getchar() to read entered char](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/stdin%20and%20stdout%20API.md#getchar-putchar)
