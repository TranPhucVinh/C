# Fundamental concepts

* [stdio](stdio)
* [File I/O system call](System%20call)
* [pipe](pipe.md)
* [FIFO](FIFO)
* [stat](stat.md)
* [uio](uio)

# Read entered value from stream in

Method to read entered value from stream in with fix bufffer size to store the entered string/value:
* [scanf()](stdio/stdin%20and%20stdout%20API.md#scanf) and [fgets()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/File%20pointer%20API.md#fgets)
* [read() system call with stdin file descriptor (STDIN_FILENO) to read the entered string in terminal](System%20call/Device%20file%20operations.md#terminal-operations)
* [gets() (deprecated) to read entered string](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/stdin%20and%20stdout%20API.md#gets-and-puts), [getchar() to read entered char](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/stdin%20and%20stdout%20API.md#getchar-putchar)

To read the entered string from stream to store into a char pointer by dynamically allocating with [realloc](../Memory/Dynamic%20memory%20allocation/API.md#realloc), check [realloc_string_entered.c](realloc_string_entered.c).
