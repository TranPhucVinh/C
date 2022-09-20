## Fundamental concepts

![](../Images/shared_library.png)

## Implementation

We need to compile our library source code into position-independent code (PIC) object file ``head.o``: ``gcc -c -fpic head.c``

Creating a shared library from an object file: ``gcc -shared -o libhead.so head.o``

Linking with a shared library

```sh
gcc -L. test.c -lhead
```
