# Features

* Display the kernel log by realtime as printing out every new kernel log in the system. 
* As realtime displaying, running it for the first time will print out not thing. Then, inserting or removing a kernel module will result in that module's kernel log printed out by this program.
* The general idea to achieve those features is to accessing to [/dev/kmsg](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/Device%20files/dev.md#devkmsg), a character device node provides userspace access to the kernel's ``printk`` buffer.

Run ``./build.sh`` to overwrite the ``kmess`` command.

**Remove**: Remove that command/program manually ``sudo rm /usr/local/bin/kmess``

**Program**: [kmess]

# Options

Kernel module for testing with the following options:

```c
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int init_module(void)
{
        printk(KERN_INFO "ubuntu line 1\n");
		printk(KERN_INFO "ubuntu line 2\n");
		printk("No line\n");
        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "clean up module\n");
}
```

## -e

``-e``: Behavior like ``grep -e``

E.g:

``kmess -e "ubuntu"`` will find all newly appeared kernel message that includes ``ubuntu``, which result in (with both ``insmod`` and ``rmmod``)

```
[ 36510.070860] ubuntu line 1
[ 36510.025822] ubuntu line 2
```

## -v

``-v``: Behavior like ``grep -v``

E.g:

``kmess -e "ubuntu"`` will find all newly appeared kernel message that doesn't include ``ubuntu``, which result in (with both ``insmod`` and ``rmmod``)

```
[ 36510.070860] No line
[ 36513.025822] clean up module
```

## -i

``-i`` will ignore case sensitive. ``-i`` by default goes with ``-v``, i.e ``-iv``.

``kmess -iv "Ubuntu"`` will result in (with both ``insmod`` and ``rmmod``):

```
[ 36510.070860] clean up module
[ 36513.025822] No line
```

``kmess -ie "Ubuntu"`` will result in (with both ``insmod`` and ``rmmod``):

```
[ 36668.974698] ubuntu line 1
[ 36668.974699] ubuntu line 2
```
## -m

``-m``: Will display multi-lines kernel message (i.e include ``\n`` in one ``printk()`` call)

E.g: For ``printk("line 1\nline 2\n")`` in kernel module

Calling ``kmess -m`` results in

```
[ 36064.627672] line 1
line 2
```

Calling ``kmess`` results in:

```
[ 35922.020519] line 1\x0aline 2
```
