# Sharing variables and functions between multiple kernel modules

```
working_folder
|--kernel_module_1
    |--kernel_module_1.c
    |--Makefile
|--kernel_module_2
    |--kernel_module_2.c
    |--Makefile
```

``kernel_module_1.c`` will export variable ``a`` and ``display_string()`` for ``kernel_module_2`` to use:

```c
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int a = 123;
void display_string(void);
EXPORT_SYMBOL(a);
EXPORT_SYMBOL(display_string);

int init_module(void)
{
	printk("This is Kernel module 1\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "clean up module\n");
}

void display_string(void){
    printk(KERN_INFO "Kernel module 1 display string\n");
}
```

``kernel_module_1`` has the default [Kernel module Makefile](https://github.com/TranPhucVinh/C/tree/master/Kernel/Loadable%20kernel%20module#implementations)

Then build and insert this kernel module: ``kernel_module_1.ko``

``kernel_module_2.ko`` will get variable ``a`` and ``display_string()`` from ``kernel_module_1.ko``

```c
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

//extern will inform the OS that variable a and display_string() are somewhere else
extern int a;
extern void display_string(void);

int init_module(void)
{
    display_string();
    printk("Value a is %d\n", a);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "clean up module\n");
}
```

``Makefile`` of ``kernel_module_2``:

```Makefile
KM2    := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
KBUILD_EXTRA_SYMBOLS := $(KM2)/../kernel_module_1/Module.symvers

obj-m := kernel_module_2.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

``KBUILD_EXTRA_SYMBOLS`` will inform ``kernel_module_2`` about the extra symbol defined in ``kernel_module_1``. The symbols built from ``kernel_module_1`` are stored in its ``Module.symvers`` file.

Then build and insert this kernel module: ``kernel_module_2.ko``

After that, ``kernel_module_1`` will be used by ``kernel_module_2``. ``lsmod`` will give:

```
Module                  Size  Used by
kernel_module_2    16384  0
kernel_module_1    16384  1 kernel_module_2
```

``rmmod kernel_module_1`` gives error ``ERROR: Module kernel_module_1 is in use by: kernel_module_2``

To remove ``kernel_module_1``, user has to remove ``kernel_module_2``.

**Note**: ``kernel_module_1`` (include ``EXPORT_SYMBOL()`` for variable ``a`` must be inserted first in order for ``kernel_module_2`` to be installed. If ``kernel_module_1`` is not installed, when installing ``kernel_module_2``, there will be error:

```
insmod: ERROR: could not insert module kernel_module_2.ko: Unknown symbol in module
```

That happen as variable ``a`` is not defined.