# Dynamic allocation

Check [dynamic allocation document folder](Dynamic%20allocation)

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

# Kernel thread

Check [kernel thread document](Kernel%20thread.md)