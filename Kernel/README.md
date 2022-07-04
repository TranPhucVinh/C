# Dynamic allocation

[Dynamic allocation example with kmalloc()](dynamic_allocation.c)

# GPIO

## API

In the latest Linux kernel versions, GPIO allocation before used are no longer require. GPIO setup I/O functions can be use directly:

```c
int gpio_direction_input(unsigned int gpio);
int gpio_direction_output(unsigned int gpio, int value);
```

**Example**: Unable to implemented on Ubuntu, check the corresponding example in Raspbian for [blink LED](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Kernel/blink_led.c)