## Fundamental concepts

A loadable kernel module (LKM) is an object file that contains code to extend the running kernel, or so-called base kernel, of an operating system. LKMs are typically used to add support for new hardware (as device drivers) and/or filesystems, or for adding system calls.

## Implementations

All kernel modules are stored in ``/lib/modules``

It is better to create a folder for working with the loadable kernel module, the folder must not include space, like ``Ubuntu_Kernel_Module``. If having spaces like ``Ubuntu Kernel Module``, the kernel module is unable to be built.

``Makefile`` to build the kernel module:

```
obj-m := test.o

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

### Source code

``ubuntu_kernel_module.c``: The very first kernel module built on Ubuntu 16.04

**Result**

Run ``dmesg|grep loadable_kernel_module`` to detect what is printed to the kernel log ``printk()``.

Run ``dmesg|tail`` to view last lines of the kernel log.

**Notice**: Without ``MODULE_LICENSE("GPL")`` there will be warning

```
[12609.519833] ubuntu_kernel_module: module license 'unspecified' taints kernel.
```

### Out of tree

Check [out of tree document](Out%20of%20tree.md) to perform out of tree in kernel module.

### Makefile

``obj-m``: Specify built object's name

With ``obj-m := <module_name>.o``, the ``kbuild`` system will build ``<module_name>.o`` from ``<module_name>.c``,
and, after linking, will result in the kernel module ``<module_name>.ko``.

``module_name-y``:

When the module is built from multiple sources, an additional line is needed listing the files: ``module_name-y := src1.o src2.o``

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

### atomic_read() and atomic_set()

```c
typedef struct {
	int counter;
} atomic_t;
```

```c
int atomic_read(const atomic_t * v);
```

Return the value of v

```c
#define atomic_set(v, i)        ((v)->counter = (i))
```

Set the value to v

* ``v``: pointer of type atomic_t
* ``i``: value

**Example**: Get and set value to atomic_t with ``atomic_read()`` and ``atomic_set()``

```c
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");

atomic_t a;

int init_module(void)
{
	a.counter = 12;
	int b = atomic_read(&a);
	printk(KERN_INFO "b %d\n", b);//b 12
	atomic_set(&a, 34);
	printk(KERN_INFO "%d\n", atomic_read(&a));//34
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "clean up module\n");
}
```

### container_of()

``container_of()`` is a macro defined in <linux/kernel.h>, which is used to return the address of the container structure of the member.

``container_of(ptr, type, member)``:

* ptr – the pointer to the member.
* type – the type of container struct this is embedded in.
* member – the name of the member within the struct.

**Example**

```c
struct struct_data_type {
	int id;
	char string_value[50];
};
    
struct struct_data_type object;
    

int init_module(void)
{    
    printk("Address of id member %p\n", container_of(&object.id, struct struct_data_type, id));
    printk("Address of string_value member %p\n", container_of(&object.string_value, struct struct_data_type, string_value));

	return 0;
}

void cleanup_module(void)
{   
	printk(KERN_INFO "clean up module\n");
}
```

### Debug with pr_debug()

Debug log can be view with ``pr_debug()``. Kernel module then needs to be built with debug flag.

Add ``debug`` target to makefile

```Makefile
obj-m += ubuntu_kernel_module.o
MY_CFLAGS += -g -DDEBUG
ccflags-y += ${MY_CFLAGS}
CC += ${MY_CFLAGS}

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

debug:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
	EXTRA_CFLAGS="$(MY_CFLAGS)"

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

Then ``insmod ubuntu_kernel_module.ko`` file built from  ``make debug``.

``pr_debug()`` can then be view:

```c
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int init_module(void)
{
    pr_debug("pr_debug Hello, World !\n");
    return 0;
}

void cleanup_module(void)
{
    pr_debug("KERN_INFO clean up module\n");
}
```
