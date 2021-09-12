``module_param()`` macro takes 3 arguments: the name of the variable, its type and permissions for the corresponding file in ``sysfs``.

```c
module_param(variable_name, variable_type , permissions);
```

Function ``module_param()`` must be outside ``init_module()``.

Before inserting module parameter, ``/sys/module/ubuntu_kernel_module$`` will have:

```sh
coresize  holders  initsize  initstate  notes  refcnt  sections  srcversion  taint  uevent
```

Then insert module parameters with ``module_param()``

```c
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int number = 9;

//Must be outside init_module()
module_param(number, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

int init_module(void)
{
        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "clean up module\n");
}
```

Then module parameter, ``/sys/module/ubuntu_kernel_module$`` will have (has ``parameter`` folder):

```
coresize  holders  initsize  initstate  notes  parameters  refcnt  sections  srcversion  taint  uevent
```

Folder ``parameters`` will have ``number``. ``cat number`` return ``9``.

To overwrite the value of ``number``:

```
sudo insmod ubuntu_kernel_module.ko number=1234
```

Then ``cat number`` return ``1234``.

Parameter variable doesn't require initiliaze:

```c
int number;

module_param(number, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
```