# OS overview

A 32-bit computer is the computer with totally 2^32 registers. 32-bit computer doesn't mean all of its registers are 32-bit.

An OS in general does 3 main work:

* Process management
* Memory management
* Scheduling

**Scheduling**: The scheduler determines which task to execute. There are few mechanisms controlling access to CPU for tasks (timeslice, preemption, idle)

In computing, a **system image** is a serialized copy of the entire state of a computer system stored in some non-volatile form such as a file. This can be an OS image, disk image and process image.

# RTOS

RTOS is an OS for real-time applications as well as it gives real-time responses to its related events. That happens as scheduler inside the RTOS takes a very short time when switching between the tasks/context switching which makes us feel like the RTOS has realtime response to the events.

The RTOS also has short latency when handling with interrupt, as well as having reliable and timebound when doing inter-task communication.

**Schedule**

RTOS uses pre-emptive scheduling. In pre-emptive scheduling, the higher priority task can interrupt a running process and the interrupted process will be resumed later.

**Inter-task Communication**

* Signal Events: Synchronize between tasks
* Message queue: Exchange message between tasks, acting like FIFO
* Mail queue: Exchange data between tasks, using queue

**Resource Sharing**:

* Semaphores: Accessing resource continuously from multiple tasks
* Mutex: Synchronize resource accessing using Mutual Exclusion
# Embedded Linux

Embedded Linux is the usage of the Linux kernel and various open-source components in embedded systems.

**Embedded Linux vs Desktop Linux**

Desktop Linux, which are also **Linux distribution**, are Ubuntu, Gentoo, Debian,... But these Dekstop Linux are not well suited for embedded system and hard to customize. Those Linux distribution have a preselected kernel version and a root filesystem with a preselected set of libraries, utilities and applications.

EMAC OE linux is an Embedded Linux. EMAC OE is EMAC's standard Linux distribution, based on the OpenEmbedded build framework for embedded Linux systems.

**Main components of a Linux embedded system**

* **Bootloader**
* [Kernel](#kernel)
* **System call interface**
* **C-Runtime library**
* **System shared libraries** 
* **Root filesystem**

When an embedded Linux is commercialized, e.g Raspberry Pi board, IMX board, Beaglebone board, their vendors will provide us the 4 main components (Bootloader, Kernel, Rootfs and toolchain) in a single package, known as  **BSP** - **Board Support Package**.

Embedded Linux software development can be separated into 3 categories:
* Linux system programming: Linux IPC (FileIO, Process, Thread, Signal, etc), multithread programming
* Linux Porting: Optimize and customize embedded Linux system. This requires knowledge on Makefile, shell scripts; build system like build-root, yocto; OS booting process, bootloader modification, rootfs package modification
* Linux device driver: Develop driver for I2C, SPI, UART, USB, Watchdog,…

# Building a Linux Embedded System
Building an embedded Linux system requires:
1. A cross toolchain.
2. Select the different packages that will run on the target (Bootloader, Kernel and Root filesystem).
3. Configure and build these packages
4. Deploy them on the device.

There are 2 ways to build an embedded linux system:

1. **Manually (creating your own scripts)**: It requires a good understanding of the software component installation process. For example, create a root filesystem from the ground up by yourself means:
  * Download the source code of all software components (libraries, utilities, or applications).
  *	Solve all dependencies and version conflicts and apply patches.
  *	Configure each software component.
  *	Cross-compile each software component.
  *	Install each software component.
2. **Using Build frameworks (e.g., Buildroot, Yocto)**: This option allows you to customize and reproduce builds easily. This is becoming the most popular option in the Linux embedded space. A Build framework typically consists of scripts and configuration meta-data that control the build process. The Build framework typically downloads, configures, compiles and installs all required components of the system taking version conflicts and dependencies into account. It allows for example to create a customized root filesystem. **The Build framework output is a complete image including toolchain, bootloader, kernel and root filesystem**.
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

