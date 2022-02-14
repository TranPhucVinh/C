The device model involves terms like **device**, **driver**, and **bus**:
* **device**: a physical or virtual object which attaches to a bus.
* **driver**: a software entity which may probe for and be bound to devices, and which can perform certain management functions.
* **bus**: a device which serves as an attachment point for other devices.

## The Simplest Drivers

User space applications are not allowed to access peripheral registers, storage media or even RAM memory directly. Instead, the hardware is accessed via kernel drivers, and RAM memory is managed by the memory management unit (MMU), with applications operating on virtual addresses.

Device drivers can be kernel modules or statically built into the kernel image. The default kernel builds most drivers into the kernel statically, so they are started automatically. A kernel module is not necessarily a device driver; it is an extension of the kernel. The kernel modules are loaded into virtual memory of the kernel. Building a device driver as a module makes the development easier since it can be loaded, tested, and unloaded without rebooting the kernel. The kernel modules are usually located in ``/lib/modules/<kernel_version>/`` on the root filesystem.

![](https://github.com/TranPhucVinh/Kicad/blob/master/Images/device_driver.png)

A device driver has 3 sides:

* One side talk to the rest of the kernel.
* One talk to the hardware
* One talk to the user

## Character Drivers

Linux requires a mechanism to transfer data from the kernel to user space. This transfer of data is handled via device nodes, which are also known as virtual files.

Each device has a unique driver that handles requests from user applications that are eventually passed to the core. Linux supports three types of devices: **character devices**, **block devices** and **network devices**.

**Character devices** are read and written directly without buffering, for example, keyboards, monitors, printers, serial ports, etc. 

**Block devices** can only be written to and read from in multiples of the block size, typically 512 or 1024 bytes. They may be randomly accessed i.e., any block can be read or written no matter where it is on the device. A classic example of a block device is a hard disk drive. 

**Network devices** are accessed via the BSD socket interface and the networking subsystems.

Drivers that have been compiled into the kernel directly register their objects with a ``sysfs`` as they are detected by the kernel. For drivers compiled as modules, this registration will happen when the module is loaded.

In Linux, every device is identified by two numbers: a **major number** and a **minor number**. When accessing a device file, the major number selects which device driver is being called to perform the input/output operation. The major number is used by the kernel to identify the correct device driver when the device is accessed. The role of the minor number is device dependent, and is handled internally within the driver. 

For instance, the i.MX7D has several hardware UART ports. The same driver can be used to control all the UARTs, but each physical UART needs its own device node, so the device nodes for these UARTS will all have the same major number, but will have unique minor numbers.
