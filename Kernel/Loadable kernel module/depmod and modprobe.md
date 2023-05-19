# depmod

``depmod`` will generate ``modules.dep`` and map files for system kernel modules.

``-a``: Probe all modules. This option is enabled by default if no file names are given in the command-line. Any changes (create or remove) with kernel modules in ``/lib/modules/$(uname -r)`` needs running ``sudo depmod -a`` again for latest update in ``modules.dep``.

``depmod`` is used to setup for [modprobe](#modprobe) (to ``insmod``/``rmmod`` kernel modules) and to load a module at boot time (with [/etc/modules](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/File%20system/File%20hierarchy.md#modules) or ``/etc/modules-load.d/modules.conf``).

# modprobe

To load/unload (remove) a module with modprobe

**Precondition**: ``ubuntu_kernel_module.ko`` located in directory ``~/username/module``:

**Step 1**: Copy ``ubuntu_kernel_module.ko`` to ``/lib/modules/$(uname -r)``

```sh
username$hostname:~/username/module$ sudo cp ubuntu_kernel_module.ko /lib/modules/$(uname -r)
```

**Step 2**: Run ``depmod -a`` to update ``modules.dep`` file

```sh
username$hostname:~/username/module$ depmod -a
```

**Step 3**: 

Load/insmod that module

```sh
username$hostname:~/username/module$ sudo modprobe ubuntu_kernel_module
```

Unload/rmmod that module:

```sh
username$hostname:~/username/module$ sudo modprobe -r ubuntu_kernel_module
```

To revert the system kernel modules setup back to the original, remove ``ubuntu_kernel_module.ko`` in ``/lib/modules/$(uname -r)``, then run ``depmod -a`` again.
