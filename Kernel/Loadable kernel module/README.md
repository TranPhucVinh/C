## Fundamental concetps

A loadable kernel module (LKM) is an object file that contains code to extend the running kernel, or so-called base kernel, of an operating system. LKMs are typically used to add support for new hardware (as device drivers) and/or filesystems, or for adding system calls.

## Implementations

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

``loadable_kernel_module.o`` is the object file built from ``loadable_kernel_module.c``.

Then simply run the Makefile with ``make``

``loadable_kernel_module.ko`` files along with other files will appear.

To insert the module: ``insmod loadable_kernel_module.ko``. After inserting, module ``loadable_kernel_module`` will be available in ``/sys/module``.

To remove the module: ``rmmod loadable_kernel_module.ko``

View module information: ``modinfo loadable_kernel_module.ko``

### Examples

* ``ubuntu_kernel_module.c``: The very first kernel module built on Ubuntu 16.04

**Result**

Run ``dmesg|grep loadable_kernel_module`` to detect what is printed to the kernel log ``printk()``.

**Notice**: Without ``MODULE_LICENSE("GPL")`` there will be warning

```
[12609.519833] ubuntu_kernel_module: module license 'unspecified' taints kernel.
```

## API

### module_init() vs init_module() and module_exit() vs cleanup_module()

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

### atomic_read()

```c
typedef struct {
	int counter;
} atomic_t;
```

```c
int atomic_read(const atomic_t * v);
```

Return the value of v

**Example**: Set value to atomic_t and read its return

```c
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");

atomic_t a;

int init_module(void)
{
	a.counter = 12;
	int b = atomic_read(&a);
	printk(KERN_INFO "b %d\n", b);
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "clean up module\n");
}
```


### printk()

All ``printk()`` messages are printed to the kernel log buffer.

Log level

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
