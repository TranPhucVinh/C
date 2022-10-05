Out of tree technique will support building a kernel module with multiple library source files.

## General define

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
## Source files in the same directory

Build kernel module with source codes and header files are in the same directory ubuntu_kernel_module.c test.h test.c

```
working_folder
|--head.c
|--head.h
|--ubuntu_kernel_module.c
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

Notice that ``main_module.ko`` is the built result.

## Header file in different directory

```
working_folder
|--src
   |--head.h
|--head.c
|--ubuntu_kernel_module.c
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

## Header files and source files in different directory

```
working_folder
|--src
   |--head.c
|--inc
   |--head.h
|--ubuntu_kernel_module.c
```

```Makefile
obj-m := main_module.o
ccflags-y := -I$(src)/inc -I$(src)/src
main_module-y := src/head.o ubuntu_kernel_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
