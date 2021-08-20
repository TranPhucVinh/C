### Example 1

Using ``module_init()`` and ``module_exit()``.

```c
#include <linux/module.h>

MODULE_LICENSE("GPL");

int module_initialize(void)
{
        printk("Module initialize\n");
        return 0;
}

void module_remove(void)
{
        printk("Module remove\n");
}

module_init(module_initialize);
module_exit(module_remove);
```
**Notice**: When using ``module_init()`` and ``module_exit()``, library ``linux/kernel.h`` is not required.

Using delay with ``msleep()`` in ``linux/delay.h``

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

### Example 2

Sharing variables between multiple kernel modules

``kernel_module_1.c`` will export variable ``a``

```c
#include<linux/module.h>
#include<linux/kernel.h>

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
#include<linux/module.h>
#include<linux/kernel.h>

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
