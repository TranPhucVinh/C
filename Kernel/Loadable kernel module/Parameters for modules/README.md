# API
## module_param()
``module_param()`` macro takes 3 arguments: the name of the variable, its type and permissions for the corresponding file in ``sysfs``.
```c
module_param(variable_name, variable_type , permissions);
```
## module_param_string()
```c
module_param_string(name, string, len, perm);
```
* ``name``: the name to be displayed on ``/sys/module/$(kernel_module_name)/parameters/``

``permissions``:

* ``S_IRUSR``: Read permission bit for the owner of the file
* ``S_IWUSR``: Write permission bit for the owner of the file
* ``S_IRGRP``: Read permission bit for the group owner of the file
* ``S_IWGRP``: Write permission bit for the group owner of the file

Function ``module_param()`` must be outside ``init_module()``.
## struct kernel_param and struct kparam_string
```c
struct kernel_param {
	const char *name;//name of the kernel parameter; not kernel module name
	struct module *mod;
	const struct kernel_param_ops *ops;
	const u16 perm;
	s8 level;
	u8 flags;
	union {
		void *arg;
		const struct kparam_string *str;
		const struct kparam_array *arr;
	};
};

/* Special one for strings we want to copy into */
struct kparam_string {
	unsigned int maxlen;
	char *string;
};
```
# Create a kernel module with parameters and update those parameter value
Before inserting module parameter, ``/sys/module/ubuntu_kernel_module$`` will have:

```sh
coresize  holders  initsize  initstate  notes  refcnt  sections  srcversion  taint  uevent
```

Kernel module [insert_params.c](insert_params.c) will insert parameters with type int, string as char pointer and string as char array.

Then module parameter, ``/sys/module/ubuntu_kernel_module$`` will have (has ``parameter`` folder):

```
coresize  holders  initsize  initstate  notes  parameters  refcnt  sections  srcversion  taint  uevent
```
```sh
username@hostname:~/ ls /sys/module/ubuntu_kernel_module/parameters/
char_array_as_string  char_ptr              number
username@hostname:~/ cat /sys/module/ubuntu_kernel_module/parameters/number
9                                                                          
username@hostname:~/ cat /sys/module/test_platform_driver/parameters/char_array_as_string
Char array as string
username@hostname:~/ cat /sys/module/test_platform_driver/parameters/char_ptr
Char pointer as string
``` 

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
# Use a kernel module to modify the parameters of another kernel module

After inserting kernel module [insert_params.c](insert_params.c), we will use [modify_kernel_module_params.c](modify_kernel_module_params.c) to modify the parameters of [insert_params.c](insert_params.c)
