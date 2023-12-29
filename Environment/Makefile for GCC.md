# Makefile with $(CC)

Makefile supports ``$(CC)``, which by default is ``gcc`` and ``cc`` command:
```Makefile
build_gcc:
	@($(CC) main.c)
```
Or:
```Makefile
build_gcc:
	@(cc main.c)
```
Target ``build_gcc`` will run ``gcc main.c``.
# Makefile with gcc command
**Build and run a C source code**:
```Makefile
build_and_run: 
	@(gcc main.c)
	@(./a.out)
```
**Assign gcc command to a Makefile variable**:
```Makefile
GCC = gcc
file = test.c

compile:
	$(GCC) $(file)
```

**Working with header files**

Compile source code ``main.c`` with header files ``header.h`` and source ``head.c`` to executable file ``main``

```Makefile
GCC = gcc
main = main.c
head = head.c 

.PHONY: main

main:
	@($(GCC) $(main) $(head) -o main)

clean:
	@(rm main)
```

Target ``main`` will compile ``main.c``. Target ``clean`` will remove ``main`` (executable file)
