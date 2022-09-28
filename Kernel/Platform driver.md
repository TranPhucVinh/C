# Fundamental concepts

On embedded systems, devices are often not connected through a bus. Such devices, instead of being dynamically detected, must be statically described:

1. By **direct instantiation** of ``struct platform_device`` structures, as done on a few old ARM non-Device Tree based platforms. Definition is done in the board-specific or SoC specific code.

2. In the **Device Tree**, a hardware description file used on some architectures. The device drivers match with the physical devices described in the ``.dts`` file. After this matching, the driver's ``probe()`` function is called. An ``.of_match_table`` has to be included in the driver's code to allow this matching.

**Platform bus** has been created to handle non-discoverable devices like UART controllers, Ethernet controllers, SPI controllers, graphic or audio devices, etc. **Platform bus** support platform drivers for those devices.

The on board peripheral which connect to SPI, I2C, Ethernet,... have no capability to announce their existence on the board to the operating system by themselves. Platform devices are inherently not discoverable.

**Platform devices** should be registered very early during system boot.

The process of associating a device with a device driver is called binding.

PCI and USB devices have inbuilt intelligence to send its details to the OS. It means PCI and USB support dynamic discovery.

# API

Please note that the operations of platform driver and device tree are related to each other.

Functions to read device tree node properties like ``device_property_present()`` are only available for platform devices, running those function inside character device will result in error.

### platform_get_irq()

```c
int platform_get_irq(struct platform_device *dev, unsigned int irq_index)
```

* ``irq_index``: Index number of the IRQs inside ``interrupts`` property of the device tree node

E.g

```c
int irq = platform_get_irq(pdev, 0); 
```

This function will return the ``irq`` number; this number is usable by ``devm_request_irq()`` (``irq`` is then visible in ``/proc/interrupts``). The second argument, ``0``, says that we need the first interrupt specified in the device node. If there is more than one interrupt, we can change this index according to the interrupt we need.

# Examples

As hardware implemention like GPIO and device tree parsing are unable to perform in Ubuntu OS computer, check device tree document in Raspberry Pi C for implementations and examples of platform driver.