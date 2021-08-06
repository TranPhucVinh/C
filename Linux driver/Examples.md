### Example 1

Using ``module_init()`` and ``module_exit()``.

```c
#include <linux/module.h>
#include <linux/kernel.h>

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