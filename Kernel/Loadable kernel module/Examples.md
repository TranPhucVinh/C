# Sharing variables between multiple kernel modules

``kernel_module_1.c`` will export variable ``a``

```c
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int a = 1024;
EXPORT_SYMBOL(a);

int init_module(void)
{
	printk("This is Kernel module 1\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "clean up module\n");
}
```

Then build and insert this kernel module: ``kernel_module_1.ko``

``kernel_module_2.ko`` will get variable ``a``:

```c
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

extern int a;//This inform the OS that variable a is somewhere else

int init_module(void)
{
        printk("Value a is %d\n", a);
        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "clean up module\n");
}
```

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

# Using delay with msleep() in linux/delay.h

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

int module_initialize(void)
{
	printk("Hello, World !\n");
	msleep(5000);
	printk("After 1000ms\n");
	return 0;
}
```

Header ``linux/delay.h`` provides functions for delay without sleep. These functions can be used in interrupt (atomic) context:

* ``ndelay(ns)`` - wait for given number of nanoseconds,
* ``udelay(us)`` - wait for given number of microseconds,
* ``mdelay(ms)`` - wait for given number of milliseconds.

Working with ``linux/time.h``:

```c
struct timeval {
  __kernel_time_t tv_sec; 	 /* seconds */
  __kernel_suseconds_t tv_usec; /* microseconds */
};
```

```c
#include <linux/module.h>
#include <linux/time.h>

MODULE_LICENSE("GPL");

struct timeval time_value;

int init_module(void)
{
        do_gettimeofday(&time_value);
        printk("Time: %ld\n", time_value.tv_sec);
        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "clean up module\n");
}
```
This will return: ``Time: 1631445504``