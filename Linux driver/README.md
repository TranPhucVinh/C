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

To insert the module: ``insmode test.ko``

To remove the module: ``rmmode test.ko``

### Examples

* ``ubuntu_kernel_module.c``: The very first kernel module built on Ubuntu 16.04

**Result**

Run ``dmesg|grep`` to detect what is log to the kernel by ``printk()``

**Notice**: Without ``MODULE_LICENSE("GPL")`` there will be warning

```
[12609.519833] ubuntu_kernel_module: module license 'unspecified' taints kernel.
```