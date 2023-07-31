# module_init() vs init_module() and module_exit() vs cleanup_module()

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

# struct module

```c
struct module {
    ...
    struct list_head list;
    ...
    char name[MODULE_NAME_LEN];
	/* Sysfs stuff. */
	struct module_kobject mkobj;
	struct module_attribute *modinfo_attrs;
    ...
    unsigned int taints;
    ...
};
```
# struct module_kobject
```c
struct module_kobject {
	struct kobject kobj;
	struct module *mod;
	struct kobject *drivers_dir;
	struct module_param_attrs *mp;
	struct completion *kobj_completion;
} __randomize_layout;
```
# atomic_read() and atomic_set()

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

```c
int atomic_add_return(int i, atomic_t * v);
```
Atomically adds ``i`` to ``v`` and returns ``i + v``

* ``i``: integer value to add
* ``v``: pointer of type ``atomic_t``

## Get and set value to atomic_t with ``atomic_read()``, ``atomic_set()`` and ``atomic_add_return()``

```c
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

atomic_t a;

int init_module(void)
{
	a.counter = 12;
	int b = atomic_read(&a);
	printk(KERN_INFO "b %d\n", b);//b 12
	atomic_set(&a, 34);
	printk(KERN_INFO "%d\n", atomic_read(&a));//34
	printk(KERN_INFO "%d\n", atomic_add_return(1, &a));//35
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "clean up module\n");
}
```

# container_of()

``container_of()`` is a macro defined in <linux/kernel.h>, which is used to return the address of the container structure of the member.

``container_of(ptr, type, member)``:

* ptr – the pointer to the member.
* type – the type of container struct this is embedded in.
* member – the name of the member within the struct.

## container_of() example

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

# Debug with pr_debug()

``pr_debug()`` is used to view debug log. Kernel module then needs to be built with debug flag. Without proper setup, ``pr_debug()`` won't display. 

Add ``debug`` target to makefile

```Makefile
obj-m := ubuntu_kernel_module.o
MY_CFLAGS := -DDEBUG
ccflags-y := ${MY_CFLAGS}

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

debug:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
	EXTRA_CFLAGS="$(MY_CFLAGS)"

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

``make`` or ``make all`` won't print out ``pr_debug()``.

With ``make debug``, ``pr_debug()`` can then be view:

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
