# Kernel module source files in the same location with Makefile

```
working_folder
|--km_1.c
|--km_2.c
|--Makefile
```
Where ``km_1.c`` and ``km_2.c`` are both kernel modules source codes for ``km_1.ko`` and ``km_2.ko``.

``Makefile``:
```Makefile
obj-m := $(km_name).o #km_name: Kernel module name

$(km_name):
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
Build ``km_1``: ``make km_name=km_1``
# Build kernel modules into source files folder by [using cd in Makefile](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Bash%20script/Build%20automation%20tools/Make/Fundamental%20concepts.md#cd-command)
To output build file ``km_1.ko`` and ``km_2.ko`` into ``km_1`` and ``km_2`` folders with directory tree like this:

```
working_folder
|--km_1
    |--km_1.c
    |--km_1.ko
|--km_2
    |--km_2.c
    |--km_2.ko
|--Makefile
```

```Makefile
obj-m := $(km_name)/$(km_name).o #km_name: Kernel module name

$(km_name):
	cd $(km_name) && make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

.PHONY: $(km_name)
```