In Ubuntu 18.04, ``.config`` file located in ``/usr/src/$(shell uname -r)`` (e.g ``/usr/src/linux-headers-4.15.0-213-generic``) has ``CONFIG_*`` flags like:

```c
CONFIG_64BIT=y
CONFIG_X86_64=y
CONFIG_X86=y
CONFIG_OUTPUT_FORMAT="elf64-x86-64"
CONFIG_ARCH_DEFCONFIG="arch/x86/configs/x86_64_defconfig"
...
```
``linux/kconfig.h`` helps reading the value of those ``CONFIG_*`` flags:

```C
#include<linux/module.h>
#include<linux/kernel.h>
#include <linux/kconfig.h>

MODULE_LICENSE("GPL");

int init_module(void)
{
	printk(KERN_INFO "%d\n", CONFIG_64BIT);// 1
	printk(KERN_INFO "%s\n", CONFIG_ARCH_DEFCONFIG);// arch/x86/configs/x86_64_defconfig
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "clean up module\n");
}
```