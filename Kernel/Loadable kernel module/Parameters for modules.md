``module_param()`` macro takes 3 arguments: the name of the variable, its type and permissions for the corresponding file in ``sysfs``.

```c
module_param(variable_name, variable_type , permissions);
```
```c
module_param_string(name, string, len, perm);
```
* ``name``: the name to be displayed on /sys/module/$(kernel_module_name)/parameters/ 

``permissions``:

* ``S_IRUSR``: Read permission bit for the owner of the file
* ``S_IWUSR``: Write permission bit for the owner of the file
* ``S_IRGRP``: Read permission bit for the group owner of the file
* ``S_IWGRP``: Write permission bit for the group owner of the file

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

Write with echo: ``echo 10 > /sys/module/ubuntu_kernel_module/parameters/number``

Re-insert kernel module:
```
sudo insmod ubuntu_kernel_module.ko number=1234
```

Then ``cat number`` return ``1234``.

Parameter variable doesn't require initiliaze:

```c
int number;

module_param(number, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
```
