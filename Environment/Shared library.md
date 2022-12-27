## Fundamental concepts

![](Images/shared_library.png)

## Implementation

We need to compile our library source code into position-independent code (PIC) object file ``head.o``: ``gcc -c -fpic head.c``

Creating shared library ``libhead.so`` from an object file: ``gcc -shared -o libhead.so head.o``

Linking with a shared library: ``gcc -L. test.c -lhead``. After running this, ``a.out`` will be the output.

Running that ``a.out`` file will result in error:

```
./a.out: error while loading shared libraries: libhead.so: cannot open shared object file: No such file or directory
```

To run that ``a.out`` file, embedded it inside the ``LD_LIBRARY_PATH`` by running this:

```sh
username$hostname:~$ LD_LIBRARY_PATH=. ./a.out
```

To run ``a.out`` without embedding inside ``LD_LIBRARY_PATH``, shared library ``libhead.so`` must be inside ``/lib`` and ``/usr/lib``.

Copy ``libhead.so`` to ``/lib``: ``sudo cp libhead.so /lib``. Then run ``a.out`` normally. Same implementation with ``/usr/lib``.

## ldd command

``ldd`` command prints shared object dependencies. 

With shared library implementation like above, run ``ldd a.out`` will give result:

```
linux-vdso.so.1 (0x00007ffe507a8000)
libhead.so => /lib/libhead.so (0x00007f8c42f50000)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f8c42d5e000)
/lib64/ld-linux-x86-64.so.2 (0x00007f8c42f65000)
```

(``libhead.so`` is copied to ``/lib``)

If ``libhead.so`` isn't existed in ``/lib``, the result will be:

```
linux-vdso.so.1 (0x00007ffe9879d000)
libhead.so => not found
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f9b95e8c000)
/lib64/ld-linux-x86-64.so.2 (0x00007f9b9608e000)
```
