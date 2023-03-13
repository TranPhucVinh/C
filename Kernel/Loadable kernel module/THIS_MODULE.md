# Get current module information like name, version

```c
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

MODULE_VERSION("0.1.0");// Set kernel module version for THIS_MODULE->version to retrieve

int init_module(void)
{
    printk(KERN_INFO "Module name %s\n", THIS_MODULE->name);
    printk(KERN_INFO "Version %s\n", THIS_MODULE->version);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "clean up module\n");
}
```

# Get all kernel modules from THIS_MODULE

All kernel modules information are stored as a [linked list](../Linked%20list) which can be accessed from any module.

In this implementation, we will get all kernel modules' names by traversing from ``THIS_MODULE``:

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

void display_linked_list(struct module *this_module){
    struct module *position;
	int index = 1;

	printk("THIS_MODULE has name %s\n", this_module->name);

	list_for_each_entry(position, &(this_module->list), list) {
		printk("Kernel module %d has name: %s\n", index, position->name);
		index++;
	}
}

int init_module(void)
{
    display_linked_list(THIS_MODULE);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "clean up module\n");
}
```
**Result**: In ``dmesg``

```
[22029.040056] node_0 has value: ubuntu_kernel_module
[22029.040060] node_1 has value: r8153_ecm
[22029.040062] node_2 has value: cdc_ether
...
```
# try_module_get() and module_put()

``try_module_get()`` will lock the current module from being removed. To remove this module, ``module_put()`` has to be called later.

```c
#include <linux/module.h>
extern bool try_module_get(struct module *module);
static inline void module_put(struct module *module);
```

Calling ``try_module_get()`` in ``init_module()`` like this example will lock the kernel permanently from being removed. Calling ``module_put()`` won't help removing it.

```c
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int init_module(void)
{
    if (!try_module_get(THIS_MODULE)) {
        printk("Get module successfully");
    }
    return 0;
}

void cleanup_module(void)
{
    module_put(THIS_MODULE);
    printk(KERN_INFO "clean up module\n");
}
```

Calling ``rmmod`` for this kernel module results in: rmmod: ERROR: Module ``ubuntu_kernel_module`` is in use.

In this character device, call ``try_module_get()`` in init_module and allow removing it with ``module_put()`` when the character device open operation is triggered.

The program below is expanded/deprived from [create_character_device_by_seperated_operations.c](../Character device/Create character device/create_character_device_by_seperated_operations.c)

```c
int dev_open(struct inode *inodep, struct file *filep)
{
    module_put(THIS_MODULE);
	printk("open\n");
	return 0;
}
int device_init(void)
{
    if (!try_module_get(THIS_MODULE)) {
        printk("Get module successfully");
    }

	if (create_character_device(DEVICE_NAME, DEVICE_CLASS, TOTAL_MINOR, BASE_MINOR, &dev_info, &fops)){
		printk("Unable to create character device %s\n", DEVICE_NAME);
		return -1;
	}
	return 0;
}
```
**Result**:

```sh
username@hostname:~$ sudo rmmod ubuntu_kernel_module
rmmod: ERROR: Module ubuntu_kernel_module is in use
username@hostname:~$ cat /dev/fops_character_device #Trigger open() system call
username@hostname:~$ sudo rmmod ubuntu_kernel_module # Module ubuntu_kernel_module is remove successfully
```
