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

All kernel modules information are stored as a [linked list](../../Linked%20list) which can be accessed from any module.

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
