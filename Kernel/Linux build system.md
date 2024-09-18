# Building a Linux Embedded System
Building an embedded Linux system requires:
1. A cross toolchain.
2. Select the different packages that will run on the target (Bootloader, Kernel and Root filesystem).
3. Configure and build these packages
4. Deploy them on the device.

There are 2 ways to build an embedded linux system:

1. **Manually (creating your own scripts)**: It requires a good understanding of the software component installation process. For example, create a root filesystem from the ground up by yourself means:
* Download the source code of all software components (libraries, utilities, or applications).
* Solve all dependencies and version conflicts and apply patches.
* Configure each software component.
* Cross-compile each software component.
* Install each software component.
2. **Using Build frameworks (e.g., Buildroot, Yocto)**: This option allows you to customize and reproduce builds easily. This is becoming the most popular option in the Linux embedded space. A Build framework typically consists of scripts and configuration meta-data that control the build process. The Build framework typically downloads, configures, compiles and installs all required components of the system taking version conflicts and dependencies into account. It allows for example to create a customized root filesystem. **The Build framework output is a complete image including toolchain, bootloader, kernel and root filesystem**.
# KBuild
## config file for KConfig in Ubuntu PC

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
## config file for KConfig in other ARM Linux single board computer
In ARM Linux single board computer, config files are treated different as it depends on the distro build process of that board.

* In [Raspbian Raspberry Pi](https://github.com/TranPhucVinh/Raspberry-Pi-GNU/blob/main/Kernel/README.md#kconfig-configs-kernel-module-which-stores-raspbian-configuration), file ``config.gz``, which stores file ``config`` for ``CONFIG_*`` flags, will be exported to ``/proc`` just only when module ``configs`` is inserted: ``sudo modprobe configs``
* In [Armbian Orange Pi](https://github.com/TranPhucVinh/Orange-Pi/blob/master/README.md#config-file-for-kconfig-in-armbian-orange-pi-zero-board), ``config.gz`` file, which stores file ``config`` for ``CONFIG_*`` flags, is available by default in ``/proc``
