# Fundamental concepts

* [Function and variable](Function%20and%20variable)
* [Header](https://github.com/TranPhucVinh/C/tree/master/Introduction/Header)
* [Macro](https://github.com/TranPhucVinh/C/tree/master/Introduction/Macro)
* [Data type](https://github.com/TranPhucVinh/C/tree/master/Introduction/Data%20type)
* [Keywords](https://github.com/TranPhucVinh/C/tree/master/Introduction/Keywords)
* [Data structure](https://github.com/TranPhucVinh/C/tree/master/Introduction/Data%20structure)
* [Linkage](Linkage.md)

### Function overloading

C doesn't support function overloading as it is not an OOP language

For function overloading in ``CPP``, check ``Function.md`` in ``Cplusplus\Introduction``.

### Default arguments

C doesn't support default arguments.

For default arguments in ``CPP``, check ``Function.md`` in ``Cplusplus\Introduction``.

### Error handling

For error handling with ``errno``, check [errno document](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/System%20call/fcntl.md#errno).

C doesn't support exception handling, ``try catch`` and ``throw`` are not available in C with GCC.

### Get libc version

```c
#include <gnu/libc-version.h>
printf("%s\n", gnu_get_libc_version());
```

# Examples

[Examples](https://github.com/TranPhucVinh/C/tree/master/Introduction/Examples)
