# [Fundamental concepts](Fundamental%20concepts)
* Process terminologies: Definition, process ID, view process information, stages of a Linux process, background process and job
* Process API and commands

# Inter-process communication

IPC (Inter-Process Communication) refers to a set of mechanisms that allow processes to communicate with each other and synchronize their actions in a Linux environment. There are two main aspects of IPC:
1. **Data Exchange**: This involves sending and receiving data between processes. The communication can be achieved through mechanisms like:
* [pipe](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/pipe.md): Used for one-way communication between a parent and child process.
* [File IO](../File%20IO/): Files can act as a medium to share data between processes.
* [Message queue](Message%20queue): Allow messages to be exchanged between processes asynchronously.
* [Shared memory](Shared%20memory): A region of memory accessible by multiple processes, offering the fastest data exchange.
* [Socket](https://github.com/TranPhucVinh/C/tree/master/Transport%20layer): Enable communication between processes in the same or across different systems. 
* [Signal](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Signal): Simple communication via notifications to signal events or state changes between processes.
2. **Synchronization**: Ensures processes are properly coordinated, especially when accessing shared resources. This is typically handled by [Semaphore](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Documents/Semaphore.md)
  
Command [ipcs](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/Process/System%20V%20IPC.md#ipcs) is useful for checking the message queue, shared memory and semaphore information.

## RPC

In distributed computing, a **remote procedure call** (**RPC**) is when a computer program causes a procedure (subroutine) to execute in a different address space (commonly on another computer on a shared network), which is written as if it were a normal (local) procedure call. This is **a form of client–server interaction** (**caller** is **client**, **executor** is **server**), typically implemented via a request–response message-passing system. 

**RPCs are a form of inter-process communication (IPC)**, in that different processes have different address spaces: if on the same host machine, they have distinct virtual address spaces, even though the physical address space is the same; while if they are on different hosts, the physical address space is different.
# [Process cloning](Process%20cloning)
