### Example 1

Using ``module_init()`` and ``module_exit()``.

```c
#include <linux/module.h>

MODULE_LICENSE("GPL");

int module_initialize(void)
{
        printk("Module initialize\n");
        return 0;
}

void module_remove(void)
{
        printk("Module remove\n");
}

module_init(module_initialize);
module_exit(module_remove);
```
**Notice**: When using ``module_init()`` and ``module_exit()``, library ``linux/kernel.h`` is not required.

Using delay with ``msleep()`` in ``linux/delay.h``

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