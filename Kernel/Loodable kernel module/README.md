All kernel modules are stored in ``/lib/modules``

It is better to create a folder for working with the loadable kernel module, the folder must not include space, like ``Ubuntu_Kernel_Module``. If having spaces like ``Ubuntu Kernel Module``, the kernel module is unable to be built.

``Makefile`` to build the kernel module:

```
obj-m += test.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

``test.o`` is the object file built from ``test.c``.

Then simply run the Makefile with ``make``

``test.ko`` files along with other files will appear.

To insert the module: ``insmod test.ko``

To remove the module: ``rmmod test.ko``

View module information: ``modinfo test.ko``

### Examples

* ``ubuntu_kernel_module.c``: The very first kernel module built on Ubuntu 16.04

**Result**

Run ``dmesg|grep`` to detect what is printed to the kernel log ``printk()``.

**Notice**: Without ``MODULE_LICENSE("GPL")`` there will be warning

```
[12609.519833] ubuntu_kernel_module: module license 'unspecified' taints kernel.
```

## API

``module_init()`` vs ``init_module()`` and ``module_exit()`` vs ``cleanup_module()``

Define in ``linux/init.h``

```c
/* Each module must use one module_init(). */
#define module_init(initfn)                 \
static inline initcall_t __inittest(void)       \
{ return initfn; }                  \
int init_module(void) __attribute__((alias(#initfn)));

/* This is only required if you want to be unloadable. */
#define module_exit(exitfn)                 \
static inline exitcall_t __exittest(void)       \
{ return exitfn; }                  \
void cleanup_module(void) __attribute__((alias(#exitfn)));
```

### printk() and log level

| Name| Alias function |
| ------- |:------:|
| KERN_EMERG    | ``pr_emerg()``    |
| KERN_ALERT    | ``pr_alert()``   |
| KERN_CRIT    | ``pr_crit()``|
|KERN_ERR |``pr_err()``|
|KERN_WARNING|``pr_warn()``|
|KERN_NOTICE|``pr_notice()``|
|KERN_INFO|``pr_info()``|
|KERN_DEBUG|``pr_debug()`` and ``pr_devel()`` if DEBUG is defined|
|KERN_DEFAULT||
|KERN_CONT|``pr_cont()``|