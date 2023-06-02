# Fundamental concepts

A loadable kernel module (LKM) is an object file that contains code to extend the running kernel, or so-called base kernel, of an operating system. LKMs are typically used to add support for new hardware (as device drivers) and/or filesystems, or for adding system calls.

# Build the very first kernel module

All OS built-in kernel modules are stored in ``/lib/modules``.

It is better to create a folder for working with the loadable kernel module, the folder must not include space, like ``Ubuntu_Kernel_Module``. If having spaces like ``Ubuntu Kernel Module``, the kernel module is unable to be built.

``Makefile`` to build the kernel module:

```Makefile
obj-m := loadable_kernel_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
Parameters:
* ``loadable_kernel_module.o``: object file built from ``loadable_kernel_module.c``
* ``-C``: [-C option of Make](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Bash%20script/Build%20automation%20tools/Make/Syntax.md#-c-option) which changes to the location on the compiler used to build the kernel module
* ``M=$PWD``: Informs kbuild that an external module is being built. The value given to ``M`` is the absolute path of the directory where the external module (kbuild file) is located.
* ``make clean`` will clean all build file in the current folder

With the ``Makefile`` above, simply run the Makefile with ``make``.

``loadable_kernel_module.ko`` files along with other files will appear.

To insert the module: ``insmod loadable_kernel_module.ko``. After inserting, module ``loadable_kernel_module`` will be available in ``/sys/module``.

To remove the module: ``rmmod loadable_kernel_module.ko``

View module information: ``modinfo loadable_kernel_module.ko``

Kernel module loaded manually by ``insmod`` will be removed when system is rebooted, setup this kernel module with [depmod](depmod%20and%20modprobe.md#depmod) and [/etc/modules](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/File%20system/File%20hierarchy.md#modules) to make it loaded automatically when system is booted.

To show which loadable kernel modules are currently loaded: ``lsmod``

## Source code

``ubuntu_kernel_module.c``: The very first kernel module built on Ubuntu 16.04

**Result**

Run ``dmesg|grep loadable_kernel_module`` to detect what is printed to the kernel log ``printk()``.

Run ``dmesg|tail`` to view last lines of the kernel log.

**Notice**: Without ``MODULE_LICENSE("GPL")`` there will be warning

```
[12609.519833] ubuntu_kernel_module: module license 'unspecified' taints kernel.
```

Function in kernel module source code without parameter must be declared with ``void`` as parameter, like this:

```c
void display_string(void){
    printk(KERN_INFO "Hello, World !\n"); 
    return 0;
}

int init_module(void)
{
    display_string();
    return 0;
}
```

If declaring ``void display_string()``, there will be error: ``error: function declaration isn’t a prototype [-Werror=strict-prototypes]``

## Makefile

### obj-m

``obj-m`` will specify built object's name

With ``obj-m := <module_name>.o``, the ``kbuild`` system will build ``<module_name>.o`` from ``<module_name>.c``,
and, after linking, will result in the kernel module ``<module_name>.ko``.

### module_name-y

To build kernel module ``main_module.ko`` from source code ``ubuntu_kernel_module.c``, we use the ``module_name-y`` method:

```Makefile
obj-m := main_module.o
main_module-y := ubuntu_kernel_module.o
```

For the kernel module built from multiple sources: ``module_name-y := src1.o src2.o``
### ccflags-y
``ccflags-y`` is available only in Linux Kernel Makefile. ``ccflag-y`` supports using "GCC flag type" like ``-I``, ``-D``,... in KBuild.

E.g: Enable macro ``DEFINE_NUM`` in kenel source file:

```c
#ifdef DEFINE_NUM
	int number = 12;
#else
	int number = 34;
#endif

int init_module(void)
{
    printk("number: %d\n", number);
    return 0;
}
```
``Makefile``
```Makefile
obj-m 		:= ubuntu_kernel_module.o
ccflags-y 	:= -DDEFINE_NUM

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
# Build multiple kernel modules by a single Makefile

* [Kernel module source files in the same location with Makefile]()
* [Build kernel modules into source files folder by using cd in Makefile]()

# [Out of tree](Out%20of%20tree.md)

Out of tree technique will support building a kernel module with multiple library source files.

Out of tree implementations include:
* [Source files in the same directory](Out%20of%20tree.md#source-files-in-the-same-directory)
* [Header file in different directory](Out%20of%20tree.md#header-file-in-different-directory)
* [Header files and source files in different directory](#header-files-and-source-files-in-different-directory)
* [Sharing variables and functions between multiple kernel modules](Sharing%20variables%20and%20functions%20between%20multiple%20kernel%20modules.md)

## Kernel module information

### Get module name

Get module name by ``THIS_MODULE->name``:
```c
printk(KERN_INFO "Module name %s\n", THIS_MODULE->name);
```

### [Parameters for modules](Parameters%20for%20modules.md)

Get modules parameters and passing command line arguments to a module

### [THIS_MODULE](THIS_MODULE.md)

THIS_MODULE is a struct object of [struct module](API.md#struct-module) which is used to indicate to the current module to access its information.

# [API](API.md)

* [module_init() vs init_module() and module_exit() vs cleanup_module()](API.md#module_init-vs-init_module-and-module_exit-vs-cleanup_module)
* [struct module](API.md#struct-module)
* [atomic_read() and atomic_set()](), example: [Get and set value to atomic_t with atomic_read(), atomic_set() and atomic_add_return()]()
* [container_of()]() and [example]()
* [Debug with pr_debug()]()
* [Using delay with msleep() in linux/delay.h]()
