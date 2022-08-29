# Fundamental concepts

On embedded systems, devices are often not connected through a bus. Such devices, instead of being dynamically detected, must be statically described:

1. By **direct instantiation** of ``struct platform_device`` structures, as done on a few old ARM non-Device Tree based platforms. Definition is done in the board-specific or SoC specific code.

2. In the **Device Tree**, a hardware description file used on some architectures. The device drivers match with the physical devices described in the ``.dts`` file. After this matching, the driver's ``probe()`` function is called. An ``.of_match_table`` has to be included in the driver's code to allow this matching.

**Platform bus** has been created to handle non-discoverable devices like UART controllers, Ethernet controllers, SPI controllers, graphic or audio devices, etc. **Platform bus** support platform drivers for those devices.

The on board peripheral which connect to SPI, I2C, Ethernet,... have no capability to announce their existence on the board to the operating system by themselves. Platform devices are inherently not discoverable.

**Platform devices** should be registered very early during system boot.

The process of associating a device with a device driver is called binding.

PCI and USB devices have inbuilt intelligence to send its details to the OS. It means PCI and USB support dynamic discovery.
