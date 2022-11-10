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

# GPIO

## GPIO API

In the latest Linux kernel versions, GPIO allocation before used are no longer require. GPIO output value can be set directly

```c
int gpio_direction_output(unsigned int gpio, int value);
void gpio_set_value(unsigned int gpio, int value);
```

GPIO input value can be get:

```c
int gpio_get_value(unsigned int gpio);
```

**Example**: Unable to implemented on Ubuntu, check the corresponding examples in Raspbian for [blink LED](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Kernel/blink_led.c) and [control LED with button](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Kernel/control_led_with_button.c).

## ioremap

When access passes though page tables, the kernel must first arrange for the physical address to be visible from your driver, and this usually means that you must call ioremap before doing any I/O. 

```c
void *ioremap(unsigned long phys_addr, unsigned long size);
```

``ioremap()`` function is used to map the physical addres of an I/O device to the kernel virtual address. Kernel creates a page table i.e mapping of virtual address to the physical address requested.

A successful call to ioremap() returns a kernel virtual address corresponding to start of the requested physical address range

To read from I/O memory, use one of the following:

```c
unsigned int ioread8(void *addr);
unsigned int ioread16(void *addr);
unsigned int ioread32(void *addr);
```

There is a similar set of functions for writing to I/O memory:

```c
void iowrite8(u8 value, void *addr);
void iowrite16(u16 value, void *addr);
void iowrite32(u32 value, void *addr);
```

**Example**: Unable to implemented on Ubuntu, check the corresponding examples in Raspbian for [GPIO control with ioremap()](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Kernel/gpio_control_with_linux_io.c) and [GPIO control with ioremap(), iowrite() and ioread()](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Kernel/gpio_control_io_rw.c).

## GPIO interrupt

Flow to register the GPIO for IRQ:

1. Allocate GPIO, for input or output mode

For input

```C
if(gpio_direction_input(GPIO)){
  printk("Unable to set GPIO %d to input\n", GPIO);
}
```

For output: ``gpio_direction_output(GPIO, 1)``

If using ``gpio_request(GPIO, LABEL)`` only and doesn't call I/O mode setup, ``request_irq()`` in step 3 will fail.

2. Convert GPIO to IRQ: ``irq_number = gpio_to_irq(GPIO)``
3. Call ``request_irq()``

**Examples**: Unable to implemented on Ubuntu, check the corresponding examples in Raspbian for [Interrupt with GPIO](https://github.com/TranPhucVinh/Raspberry-Pi-C/tree/main/Kernel#interrupt-with-gpio).

# Platform drivers

Check [Platform driver document](Platform%20driver.md)

# Device tree

Device tree file ``/sys/firmware/devicetree/`` is not available on Ubuntu 16.04 as ``dtb`` files are built-in on the kernel image. For implementation with device tree, check the corresponding document in Raspbian.
