# Fundamental concepts

If you write character drivers for simple devices, you have to create a major number as well. In such a case, the kernel has to keep that details in the static table. This means, you end up wasting the RAM for simple devices. If you write multiple character drivers for multiple simple devices, then the RAM wastage also increases. To avoid this you can use the misc driver. Because, in the misc driver, you don’t need to specify the major number since it has a fixed major number which is ``10``.

# API

The ``misc_register()`` function registers a miscellaneous device with the kernel. If the minor number is set to ``MISC_DYNAMIC_MINOR`` a minor number is dinamically assigned and placed in the minor field of the struct miscdevice structure.

```c
int misc_register(struct miscdevice *misc);
int misc_deregister(struct miscdevice *misc);
```

# Examples

## Create a miscellaneous character driver

[create_miscellaneous_device.c](create_miscellaneous_device.c)

**Result**: 

Device ``miscellaneous_device`` will then appear in ``/dev`` with major number is ``10``. ``miscellaneous_device`` folder will also appear in ``sys/class/misc``.

Before performing operation to ``miscellaneous_device``, change its mode: ``sudo chmod 777 /dev/miscellaneous_device``. Then all basic file operations can be performing to ``miscellaneous_device`` normally like with character device:

Read operation: ``cat /dev/miscellaneous_device``

Write operation: ``echo Hello > /dev/miscellaneous_device``