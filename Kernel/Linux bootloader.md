# Linux bootloader

Linux bootloader is a small amount of machine specific code to initialize the system. Its duty is to:

* Configuration of the memory system.
* Loading of the kernel image and the device tree at the correct addresses.
* Optional loading of an initial RAM disk at the correct memory address.
* Setting of the kernel command-line and other parameters (e.g, device tree, machine type)

**U-Boot** (fullname Das U-Boot) is the boot loader used in embedded devices to package the instructions to boot the device's operating system kernel. It is available for various computer architectures, like ARM, RISC-V, x86,...

**U-Boot** is the standard bootloader for ARM Linux.

# Linux booting process

Linux booting process will follow those steps:

1. The boot process begins at POR (Power On Reset) where the hardware reset logic forces the ARM core to begin execution starting from the on-chip boot ROM. The boot ROM can support several devices (e.g, NOR flash, NAND Flash, SD/eMMC). 

2. The U-Boot loads both the kernel image and the compiled device tree binary into RAM (like DDR3 RAM) and passes the memory address of the device tree binary into the kernel as part of the launch.

3. The U-Boot jumps to the kernel code.

4. Kernel runs low level kernel initialization, enabling MMU and creating the initial table of memory pages, and setting up caches. This is done in ``arch/arm/kernel/head.S``. The file ``head.S`` contains CPU architecture specific but platform independent initialization code. Then the system switches to the non architecture specific kernel startup function ``start_kernel()``.

5. Kernel runs ``start_kernel()`` located in ``init/main.c`` that:

* Initializes the kernel core (e.g., memory, scheduling, interrupts,...). 
* Initializes statically compiled drivers.
* Mounts the root filesystem based on bootargs passed to the kernel from U-Boot.
* Executes the first user process, init. The three init programs that you usually find in Linux embedded devices are BusyBox init, System V init, and systemd.

State machine for those 5 steps

![](../Environment/Images/booting_process.png)

OS source file are stored in the storage media (SD card, NAND flash,...) and is loaded into RAM when running.

6 steps detail:

* [BIOS](#BIOS): System startup/Hardware init
* Bootloader stage 1: [Master Boot Record (MBR)](#MBR) executes GRUB
* Bootloader stage 2: [GRUB](#GRUB) executes Kernel
* [Kernel](#Kernel) will executes process init located in ``/sbin/init``
* Execute [init](#init) process
* Run level: Start userspace for command line

## BIOS

BIOS (Basic Input/Output System) will perform some system integrity checks, then search, load, and executes the boot loader program.

When setting up the PC, you can press a key (typically F12 of F2, but it depends on your system) during the BIOS startup to change the boot sequence.

Once the boot loader program is detected and loaded into the memory, BIOS gives the control to it.

## MBR

MBR is located in the 1st sector of the bootable disk, typically in ``/dev/sda``. MBR contains information about GRUB 

## GRUB

* GRUB stands for Grand Unified Bootloader. If you have multiple kernel images installed on your system, you can choose which one to be executed.
* GRUB displays a splash screen, waits for few seconds, if you don’t enter anything, it loads the default kernel image as specified in the grub configuration file.
* GRUB has the knowledge of the filesystem.
* GRUB configuration file is ``/boot/grub/grub.cfg``. In Ubuntu 20.04 ``grub.cfg`` file, it contains ``initrd`` (Initial RAM Disk) image (checked by searching ``initrd`` in that file). ``initrd`` is used by kernel as temporary root file system until kernel is booted and the real root file system is mounted. It also contains necessary drivers compiled inside, which helps it to access the hard drive partitions, and other hardware.

## Kernel

* Kernel mount the root file system as specified in ``grub.cfg``.
* Kernel executes the ``/sbin/init`` program. Since init was the 1st program to be executed by Linux Kernel, it has the process id (PID) of 1. 

## init

init process will decide the run level. Ubuntu 20.04 supports [systemd](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/Systemd.md) to setup run level.

Command ``runlevel`` will print out the current runlevel number.

Run command ``man runlevel`` for ``runlevel`` manual, and to also check the meaning of the level number.

**Command**

* ``sudo init 6``: Reboot the OS