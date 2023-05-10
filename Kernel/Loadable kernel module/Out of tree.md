# General define

``ubuntu_kernel_module.c``

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include "head.h"

MODULE_LICENSE("GPL");

int init_module(void)
{
	printk(KERN_INFO "Hello, World !\n");
	add(3,4);
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "clean up module\n");
}
```

``head.h``
```c
#include <linux/kernel.h>
#include <linux/module.h>

void add(int a, int b);
```

``head.c``

```c
#include "head.h"

void add(int a, int b)
{
    printk("result: %d\n", a+b);
}
```
# Source files in the same directory

Build kernel module ``main_module.ko`` with source codes and header files are in the same directory ``ubuntu_kernel_module.c``, ``head.c`` and ``head.h``.

```
working_folder
|--head.c
|--head.h
|--ubuntu_kernel_module.c
|--Makefile
```

```Makefile
obj-m := main_module.o
main_module-y := head.o ubuntu_kernel_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

After successfully build, the files inside ``working_folder`` will be:

```
head.c  head.o          main_module.mod    main_module.mod.o  Makefile       Module.symvers          ubuntu_kernel_module.o
head.h  main_module.ko  main_module.mod.c  main_module.o      modules.order  ubuntu_kernel_module.c
```

As ``main_module.ko`` is the built result, it is built from the kernel object ``main_module.o``. ``main_module-y`` is used/required for ``main_module.o`` which requires 2 kernel object ``head.o ubuntu_kernel_module.o``

# Header file in different directory

When header or source files are in different directory, use ``ccflags-y``

```
working_folder
|--include
|   |--head.h
|--head.c
|--ubuntu_kernel_module.c
|--Makefile
```

(Don't need to change ``head.h`` path called in ``ubuntu_kernel_module.c`` and ``head.c``)

```Makefile
obj-m := main_module.o
ccflags-y := -I$(src)/include
main_module-y := head.o ubuntu_kernel_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

``ccflags-y`` is available only in Linux Kernel Makefile. ``ccflags-y := -I$(src)/include`` with ``$(src)`` provides the absolute path by pointing to the directory where the currently executing file is located. ``$(src)`` is only available with ``ccflags-y`` in Linux Kernel Makefile.

# Header files and source files in different directory

```
working_folder
|--source
|   |--head.c
|--include
|   |--head.h
|--ubuntu_kernel_module.c
|--Makefile
```

```Makefile
obj-m := main_module.o
ccflags-y := -I$(src)/include -I$(src)/source
main_module-y := source/head.o ubuntu_kernel_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
