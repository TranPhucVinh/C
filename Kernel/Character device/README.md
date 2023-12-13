# Fundamental concepts

The **device model** involves terms like **device**, **driver**, and **bus**:
* **device**: a physical or virtual object which attaches to a bus.
* **driver**: a software entity which may probe for and be bound to devices, and which can perform certain management functions.
* **bus**: a device which serves as an attachment point for other devices.

Linux supports 4 types of devices:

* **Character devices** is any device that can have streams of characters read from or written to it without buffering, for example, keyboards, monitors, printers, serial ports, terminals, etc. **Character devices** provide access for userspace to kernel space.
* **Block devices** is a device that composes of fixed-sized blocks, that can be read and write to store data. Block device can only be written to and read from in multiples of the block size, typically 512 or 1024 bytes. They may be randomly accessed i.e., any block can be read or written no matter where it is on the device. Block devices are hard disk, SD card,...
* **Network devices** are accessed via the BSD socket interface and the networking subsystems.
* **MTD devices**: MTD devices (MTD is abbreviated for **Memory Technology Device**) is a type of device file in Linux for interacting with flash memory. Flash memory is a unique device type that has translations to allow them to be used as **block** and **character devices**. For PC not supported flash memory (i.e UBIFS not existed), device file ``mtd`` like ``/dev/mtd4`` will not existed. Raspberry Pi 3B+ and Orange Pi Zero board doesn't have those device file/filesystems, too.

List all character devices and block devices with major number: ``cat /proc/devices``

## Device drivers

User space applications are not allowed to access peripheral registers, storage media or even RAM memory directly. Instead, the hardware is accessed via kernel drivers, and RAM memory is managed by the memory management unit (MMU), with applications operating on virtual addresses. 

This kinds of access or transfering of data is handled via device nodes, which are also known as virtual files. Each device has a unique driver that handles requests from user applications that are eventually passed to the core. 

Device drivers can be kernel modules or statically built into the kernel image. The default kernel builds most drivers into the kernel statically, so they are started automatically. A kernel module is not necessarily a device driver; it is an extension of the kernel. The kernel modules are loaded into virtual memory of the kernel. Building a device driver as a module makes the development easier since it can be loaded, tested, and unloaded without rebooting the kernel. The kernel modules are usually located in ``/lib/modules/<kernel_version>/`` on the root filesystem.

![](https://github.com/TranPhucVinh/C/blob/master/Environment/Images/device_driver.png)

A device driver has 3 sides:

* One side talk to the rest of the kernel.
* One talk to the hardware
* One talk to the user

Drivers that have been compiled into the kernel directly register their objects with a ``sysfs`` as they are detected by the kernel. For drivers compiled as modules, this registration will happen when the module is loaded.

In Linux, every device is identified by two numbers: a **major number** and a **minor number**. When accessing a device file, the major number selects which device driver is being called to perform the input/output operation, i.e represents the driver that the device is being controlled by. The major number is used by the kernel to identify the correct device driver when the device is accessed. The role of the minor number is device dependent, and is handled internally within the driver. 

For instance, the i.MX7D has several hardware UART ports. The same driver can be used to control all the UARTs, but each physical UART needs its own device node, so the device nodes for these UARTS will all have the same major number, but will have unique minor numbers.

## Other device files

**UBIFS** file-system stands for UBI File System. UBI stands for “Unsorted Block Images”. UBIFS is a flash file system, which means it is designed to work with flash devices. It is important to understand, that UBIFS is completely different to any traditional file-system in Linux, like Ext2, XFS, JFS, etc. UBIFS represents a separate class of file-systems which work with **MTD devices**, not block devices.
