# Dynamic allocation

[Dynamic allocation example with kmalloc()](dynamic_allocation.c)

# GPIO

## API

In the latest Linux kernel versions, GPIO allocation before used are no longer require. GPIO output value can be set directly

```c
int gpio_direction_output(unsigned int gpio, int value);
void gpio_set_value(unsigned int gpio, int value);
```

GPIO input value can be get:

```c
int gpio_get_value(unsigned int gpio);
```

**Example**: Unable to implemented on Ubuntu, check the corresponding example in Raspbian for [blink LED](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Kernel/blink_led.c) and [control LED with button](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Kernel/control_led_with_button.c).
