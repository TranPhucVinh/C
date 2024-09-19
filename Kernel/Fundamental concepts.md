# OS and embedded Linux
An OS in general does 3 main work:

* Process management
* Memory management
* **Scheduling**: The scheduler determines which task to execute. There are few mechanisms controlling access to CPU for tasks (timeslice, preemption, idle)

Embedded Linux is the usage of the Linux kernel and various open-source components in embedded systems.

**Embedded Linux vs Desktop Linux**

Desktop Linux, which are also **Linux distribution**, are Ubuntu, Gentoo, Debian,... But these Dekstop Linux are not well suited for embedded system and hard to customize. Those Linux distribution have a preselected kernel version and a root filesystem with a preselected set of libraries, utilities and applications.

EMAC OE linux is an Embedded Linux. EMAC OE is EMAC's standard Linux distribution, based on the OpenEmbedded build framework for embedded Linux systems.

**Main components of a Linux embedded system**:
* **Bootloader**
* [Kernel](#kernel)
* **System call interface**
* **C-Runtime library**
* **System shared libraries** 
* **Root filesystem**

When an embedded Linux is commercialized, e.g Raspberry Pi board, IMX board, Beaglebone board, their vendors will provide us the 4 main components (Bootloader, Kernel, Rootfs and toolchain) in a single package, known as  **BSP** - **Board Support Package**.

Embedded Linux software development can be separated into 3 categories:
* **Linux system programming**: Linux IPC, multithread programming
* **Linux porting**: Optimize and customize embedded Linux system. This requires knowledge on Makefile, shell scripts; build system like build-root, yocto; OS booting process, bootloader modification, rootfs package modification
* **Linux device driver**: Develop driver for I2C, SPI, UART, USB, Watchdog,…

# User-space and kernel-space
* **User-space** refers to the environment where user applications run, and they have limited privileges. Processes running in user-space cannot directly interact with hardware or system resources (e.g., memory, devices) and need to request services through system calls.
* **Kernel-space** is where the operating system kernel operates, with full control over the system’s hardware and resources. IPC mechanisms often involve the kernel since the kernel manages processes, memory, and hardware resources.
In terms of **IPC mechanisms**, user-space processes communicate with each other through system calls to the kernel. For example:
* When using [pipes](), [message queues](), or [shared memory](), a process in user-space makes a system call (like ``pipe()``, ``msgget()``, ``shmget()``) to request the kernel to set up and manage the IPC resources.
* The **kernel** facilitates the actual data exchange and synchronization. The kernel allocates memory, manages the resources, and ensures proper access controls between processes.
* For some IPC mechanisms like **shared memory**, after the setup by the kernel, the actual data exchange can happen directly in user-space without repeatedly going back to the kernel, making it more efficient.

In short, **user-space processes rely on the kernel** to manage IPC mechanisms, and system calls act as the bridge between user-space and kernel-space to ensure controlled and secure communication between processes.
# Linux kernel

The **Linux kernel** is the lowest level of software running on a Linux system. It is charged with managing the hardware, running user programs, and maintaining the overall security and integrity of the whole system.

Tasks performed by the kernel:

* Process scheduling
* Memory management
* Provision of a file system
* Creation and termination of processes
* Access to devices
* Networking
* Provision of a system call application programming interface (API)

Kernel can be divided into 3 types: monolithic, microkernel, and hybrid. Linux use monolithic kernel. OS X (XNU) and Windows 7 use hybrid kernel.

Android use Linux Kernel. Windows and Windows Phone use NT kernel. OS X and iOS use Darwin kernel. 

# Automotive embedded system

## OSEK

OSEK (English: "Open Systems and their Interfaces for the Electronics in Motor Vehicles") is a standards body that has produced specifications for an **embedded operating system**, a communications stack, and a network management protocol for **automotive embedded systems**. **OSEK** is an open standard, published by a consortium founded by the automobile industry. Some parts of OSEK are standardized in **ISO 17356**.

## Architecture

Layer -> Subsystem -> Component

Layer examples: Application layer, HardwareAbstraction layer

Subsystem examples: SteeringFunctions, Sensors, MicrocontrollerAbstraction

Component examples: SteeringControl, AnalogSensors, MemoryMonitor

AUTOSAR is layered architecture. Layers of AUTOSAR are **ASW**, **RTE** and **BSW**.

**AAL Layer**: The AAL-Layer provides the possibility to integrate AUTOSAR SWCs into the EPSDriveSW-Architecture.

## Abbreviations

* **ECU**: An electronic control unit (ECU) is an **embedded system** in automotive electronics that controls one or more of the electrical systems or subsystems in a vehicle.
* **VRTE**: Vehicle Runtime Environment
