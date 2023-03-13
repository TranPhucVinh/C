

# Using delay with msleep() in linux/delay.h

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

int module_initialize(void)
{
	printk("Hello, World !\n");
	msleep(5000);
	printk("After 1000ms\n");
	return 0;
}
```

Header ``linux/delay.h`` provides functions for delay without sleep. These functions can be used in interrupt (atomic) context:

* ``ndelay(ns)`` - wait for given number of nanoseconds,
* ``udelay(us)`` - wait for given number of microseconds,
* ``mdelay(ms)`` - wait for given number of milliseconds.

Working with ``linux/time.h``:

```c
struct timeval {
  __kernel_time_t tv_sec; 	 /* seconds */
  __kernel_suseconds_t tv_usec; /* microseconds */
};
```

```c
#include <linux/module.h>
#include <linux/time.h>

MODULE_LICENSE("GPL");

struct timeval time_value;

int init_module(void)
{
        do_gettimeofday(&time_value);
        printk("Time: %ld\n", time_value.tv_sec);
        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "clean up module\n");
}
```
This will return: ``Time: 1631445504``