# Fundamental concepts

A program can execute in **user mode** and **kernel mode**. If a progam is executed in user mode, it can't direct access to the memory, hardware and such resources. If a program is executed in kernel mode (kernel driver), that program has direct access to the memory, hardware,... A program on userspace takes longer time than the kernel driver to access the hardware peripheral as it needs time to make system call.

If a program is executed in **user mode** and want to access to the memory or hardware, it makes a call to the operating system, which is known as **system call**.

System call is a programmatic way/a call in which a computer program requests a service from the kernel of the operating system.

## Types of system calls

There are 5 types of system calls

* Process control
* [File manipulation](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/README.md#system-call)
* Device management
* Information maintenance
* Communications

### Process control

Process control system calls include:

* end, abort
* load, execute
* create process, terminate process
* get process attributes, set process attributes
* wait for time
* wait event, signal event
* allocate and free memory

### File manipulation

File manipulation system calls include:

* create file, delete file
* open, close
* read, write, reposition
* get file attributes, set file attributes

### Device manipulation

Device manipulation system calls include

* request device, release device
* read, write, reposition
* get device attributes, set device attributes
* logically attach or detach devices

Logically attach informs the physcially attached device is ready to use

### Information maintenance

* get time or date, set time or date
* get system data, set system data
* get process, file or device attributes
* set process, file or device attributes

### Communications

* create, delete communication connection
* send, receive messages
* transfer status information
* attach or detach remote devices
