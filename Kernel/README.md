# Loadable kernel module

To build a kernel module as a device driver, check [Loadable kernel module document folder](Loadable%20kernel%20module).

For dynamic allocation implementation in a kernel module, check [dynamic allocation document folder](Dynamic%20allocation).

For multithread handling in kernel module, check [kernel thread document folder](Kernel%20thread).

For timer implementation in kernel module, check [Timer document folder](Timer).

For linked list data structure implementation in kernel module, check [Linked list document folder](Linked%20list).

## Communication between userspace to kernel space

* [Character device](#character%20device)
* [procfs entry](procfs%20entry.md)
* [sysfs entry](sysfs%20entry.md)

# Character device

For communication between userspace and kernel space through a device file, we need to create a chracter device.

Character device folder include: 

* [Create character device](): Character device creation and basic file operations open/read/write/close document
* [Character device operations]()
* [Miscellaneous character driver](): Miscellaneous character driver creation and basic file operations

# Interrupt

For interrupt implementation and handling in kernel space for both single kernel module and character device, check [Interrupt document folder](Interrupt)

# Platform drivers and Device tree

On embedded systems, devices are often not connected through a bus. Such devices, instead of being dynamically detected, must be statically described:

1. By **direct instantiation** of ``struct platform_device`` structures, as done on a few old ARM non-Device Tree based platforms. Definition is done in the board-specific or SoC specific code.

2. In the **Device Tree**, a hardware description file used on some architectures. The device drivers match with the physical devices described in the ``.dts`` file. After this matching, the driver's ``probe()`` function is called. An ``.of_match_table`` has to be included in the driver's code to allow this matching.

**Platform bus** has been created to handle non-discoverable devices like UART controllers, Ethernet controllers, SPI controllers, graphic or audio devices, etc. **Platform bus** support platform drivers for those devices.

The on board peripheral which connect to SPI, I2C, Ethernet,... have no capability to announce their existence on the board to the operating system by themselves. Platform devices are inherently not discoverable.

**Platform devices** should be registered very early during system boot.

The process of associating a device with a device driver is called binding.

PCI and USB devices have inbuilt intelligence to send its details to the OS. It means PCI and USB support dynamic discovery.

Please note that the operations of platform driver and device tree are related to each other.

Functions to read device tree node properties like ``device_property_present()`` are only available for platform devices, running those function inside character device will result in error.

Device tree file ``/sys/firmware/devicetree/`` is not available on Ubuntu 16.04 as ``dtb`` files are built-in on the kernel image. For implementation with device tree, check [the corresponding document in Raspbian](https://github.com/TranPhucVinh/Raspberry-Pi-C/tree/main/Kernel/Device%20tree).

As hardware implemention like GPIO and device tree parsing are unable to perform in Ubuntu OS computer, check [device tree document in Raspberry Pi C](https://github.com/TranPhucVinh/Raspberry-Pi-C/tree/main/Kernel/Device%20tree) for implementations and examples of platform driver.

# Linux drivers

This is the list of Linux drivers that have been created so far:

* [GPIO driver (implemented on Raspbian)](https://github.com/TranPhucVinh/Raspberry-Pi-C/tree/main/Kernel/GPIO)
* [I2C driver: I2C driver for a specific I2C slave on an existed I2C bus (implemented on Raspbian)](https://github.com/TranPhucVinh/Raspberry-Pi-C/tree/main/Kernel#i2c-driver)
