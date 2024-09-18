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
