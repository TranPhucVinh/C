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
