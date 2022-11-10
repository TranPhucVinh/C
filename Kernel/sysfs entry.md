# Fundamental concepts

Inserting a kernel module for sysfs entry will create a directory/file inside ``sys/kernel``.

# API

### kobject_create_and_add

```c
struct kobject *kobject_create_and_add(const char *name, struct kobject *parent);
```

Create a ``struct kobject`` dynamically and register it with ``sysfs``

* ``name``: the name for the ``kobject``
* ``parent``: the parent ``kobject`` of this kobject, if any. Preferred to be ``kernel_kobj``, a predefined kernel object

### __ATTR()

```c
#define __ATTR(_name, _mode, _show, _store) {				\
	.attr = {.name = __stringify(_name),				\
		 .mode = VERIFY_OCTAL_PERMISSIONS(_mode) },		\
	.show	= _show,						\
	.store	= _store,						\
}
```

``_mode`` in ``__ATTR()`` must sastisfied all the following condition:

* ``USER_READABLE`` >= ``GROUP_READABLE`` >= ``OTHER_READABLE``
* <777 and >0
* ``USER_WRITABLE`` >= ``GROUP_WRITABLE``
* ``OTHER_WRITABLE = 0`` (as not allow other to write)

# Example

## Feature

Create a ``sysfs`` folder and a file inside it (``/sys/kernel/new_sys_kernel_dir/new_sys_kernel_file``) with those 2 features:

* Write data to that sysfs file
* Read responsed data from that sysfs file

After inserting the kernel module successfully, the sysfs entry will be ``/sys/kernel/new_sys_kernel_dir/new_sys_kernel_file``

Change its mode to 777 (as defined in API ``__ATTR()``, it must be changed by CLI): ``sudo chmod 777 /sys/kernel/new_sys_kernel_dir/new_sys_kernel_file``
 
To read (``sys_kernel_show()``): ``cat /sys/kernel/new_sys_kernel_dir/new_sys_kernel_file``

To write (``sys_kernel_store()``): ``echo 'write string' > /sys/kernel/new_sys_kernel_dir/new_sys_kernel_file`` (check written string displayed by ``dmesg``).

## Source code

```c
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/string.h>

#define SYS_KERNEL_DIR	"new_sys_kernel_dir"
#define SYS_KERNEL_FILE	"new_sys_kernel_file"//Only use this macro for debugging
#define MODE 			0770				 //_mode in __ATTR() requires OTHER_WRITABLE = 0

MODULE_LICENSE("GPL");

struct kobject *sys_kobj;

/**
 * @brief Read callback for SYS_KERNEL_DIR/SYS_KERNEL_FILE
 */
ssize_t sys_kernel_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer) {
	return sprintf(buffer, "You have read from /sys/kernel/%s/%s\n", kobj->name, attr->attr.name);
}

/**
 * @brief Write callback for SYS_KERNEL_DIR/SYS_KERNEL_FILE
 */
ssize_t sys_kernel_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count) {
	printk("'%s' is written to /sys/kernel/%s/%s\n", buffer, kobj->name, attr->attr.name);
	return count;
}

/**
 * SYS_KERNEL_FILE inside /sys/kernel/SYS_KERNEL_DIR is init in this function
 * As _name in __ATTR is formed by __stringify() so pass the value new_sys_kernel_file
 * for the file with the same name. If using macro like this
 * SYS_KERNEL_FILE	"new_sys_kernel_file" 
 * Then the file created inside /sys/kernel will be /sys/kernel/new_sys_kernel_dir/'new_sys_kernel_file'
**/
struct kobj_attribute sys_kernel_attr = __ATTR(new_sys_kernel_file, MODE, sys_kernel_show, sys_kernel_store);

int sys_init(void) {
	printk("Creating /sys/kernel/%s/%s\n", SYS_KERNEL_DIR, SYS_KERNEL_FILE);

	//Create folder SYS_KERNEL_DIR inside /sys/kernel
	sys_kobj = kobject_create_and_add(SYS_KERNEL_DIR, kernel_kobj);//Create sys_kobj dynamically
	if(!sys_kobj) {
		printk("Can't create /sys/kernel/%s\n", SYS_KERNEL_DIR);
		return -ENOMEM;
	}

	//Create file SYS_KERNEL_FILE inside /sys/kernel/SYS_KERNEL_DIR
	if(sysfs_create_file(sys_kobj, &sys_kernel_attr.attr)) {
		printk("Can't create /sys/kernel/%s/%s\n", SYS_KERNEL_DIR, SYS_KERNEL_FILE);
		kobject_put(sys_kobj);
		return -ENOMEM;
	}
	printk("Create /sys/kernel/%s/%s successfully\n", SYS_KERNEL_DIR, SYS_KERNEL_FILE);
	return 0;
}

void __exit sys_exit(void) {
	printk("Deleting /sys/kernel/%s/%s\n", SYS_KERNEL_DIR, SYS_KERNEL_FILE);
	sysfs_remove_file(sys_kobj, &sys_kernel_attr.attr);
	kobject_put(sys_kobj);
	printk("Delete /sys/kernel/%s/%s successfully\n", SYS_KERNEL_DIR, SYS_KERNEL_FILE);
}

module_init(sys_init);
module_exit(sys_exit);
```
