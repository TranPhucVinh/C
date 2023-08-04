# API
## module_param()
``module_param()`` macro takes 3 arguments: the name of the variable, its type and permissions for the corresponding file in ``sysfs``.
```c
module_param(variable_name, variable_type , permissions);
```
* ``variable_type``: int, ``charp`` (char pointer),...
## module_param_array()

```c
module_param_array(name, type, num, perm);
```
For arguments ``num``:

* If setting ``num`` to NULL, that array kernel parameters is displayed in ``/sys/module/$(kernel_module_name)/parameters/``
* If setting ``num`` to a variable like ``arr_argc``, this array kernel parameter isn't displayed in ``/sys/module/$(kernel_module_name)/parameters/``. ``arr_argc`` will have the number or array elements initialized by the user at module loading time:

```c
//Other implementations are identically to insert_params.c
int arr_argc = 0;
int int_arr[] = {1, 2};
module_param_array(int_arr, int, &arr_argc, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
int init_module(void)
{
	printk("arr_argc: %d\n", arr_argc);
	return 0;
}
```
Inserting [insert_params.ko](insert_params.c) with array values setup for ``int_arr``: ``insmod insert_params.ko int_arr=123,456``

Then in ``dmesg``: ``arr_argc: 2``

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
## module_param_cb()
``module_param_cb()`` initializes kernel module parameters along callback functions. When using ``module_param_cb()``, other module param fucntion init like ``module_param()`` can't be used.
```c
module_param_cb(name, ops, arg, perm)
```
* **name**: param name string in ``/sys/module/<kernel_module_name>/parameters/<name_string>``
* **ops**: the struct kernel_param_ops which contain pointer to handler function
* **arg**: argument variable pointer
* **perm**: permission type
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

struct kparam_string {
	unsigned int maxlen;
	char *string;
};

struct kparam_array
{
	unsigned int max;//Total member of the array
	unsigned int elemsize;//size of each element, e.g elemsize=4 byte for int array
	unsigned int *num;
	const struct kernel_param_ops *ops;
	void *elem;
};
```
## struct param_attribute and struct module_param_attrs
Both ``struct param_attribute`` and ``struct module_param_attrs`` are **defined internally** inside [linux/kernel/params.c](https://github.com/torvalds/linux/blob/master/kernel/params.c) (Official Linux repository). Copy those 2 structs to any kernel module source code that wish to parse the kernel parameters.

``struct module_param_attrs`` is a member of [struct module_kobject](https://github.com/TranPhucVinh/C/blob/master/Kernel/Loadable%20kernel%20module/API.md#struct-module_kobject)
```c
struct param_attribute
{
	struct module_attribute mattr;
	const struct kernel_param *param;
};

struct module_param_attrs
{
	unsigned int num;// number of kernel parameters of the kernel module
	struct attribute_group grp;
	struct param_attribute attrs[];
};
```
# Create a kernel module with parameters and update those parameter value
Before inserting module parameter, ``/sys/module/ubuntu_kernel_module$`` will have:

```sh
coresize  holders  initsize  initstate  notes  refcnt  sections  srcversion  taint  uevent
```

Kernel module [insert_params.c](insert_params.c) will insert parameters with [type int by module_param()](#module_param), [int array by module_param_array()](#module_param_array), [string as char pointer by module_param()](#module_param) and [string as char array by module_param_string()](#module_param_string).

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
# Create a kernel module with parameter, along with callback, and update this parameter value
With [insert_params_with_callback.c](insert_params_with_callback.ko), every time the kernel parameter is read, update, their corresponded function will be called. That's implemented by using [module_param_cb()](#module_param_cb) function.
# Use a kernel module to modify the parameters of another kernel module

After inserting kernel module [insert_params.c](insert_params.c), we will use [modify_kernel_module_params.c](modify_kernel_module_params.c) to:

* Search for a specific kernel module based on its name: [search_for_km()](modify_kernel_module_params.c#L54)
* List all parameters of the searched kernel module: [list_all_km_params()](modify_kernel_module_params.c#L75)
* Read and update the parameters of a kernel module from the current one: [read_and_update_km_parameters()](modify_kernel_module_params.c#L105)
* Read and update the array parameters of a kernel module from the current one: [read_and_update_array_km_parameters()](modify_kernel_module_params.c#L134)
