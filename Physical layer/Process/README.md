## Jobs

A job is a process that the shell manages. Each job is assigned a sequential job ID. Because a job is a process, each job has an associated PID. There are three types of job statuses:

1. **Foreground**: When you enter a command in a terminal window, the command occupies that terminal window until it completes. This is a foreground job.
2. **Background**: When you enter an ampersand (``&``) symbol at the end of a command line, the command runs without occupying the terminal window.
3. **Stopped**: If you press Control + Z for a foreground job, or enter the stop command for a background job, the job stops. 

## Inter-process communication

* [pipe](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/pipe.md)
* [FIFO](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/FIFO.md)
* Semaphore
* Message queue
* Shared memory
* [Socket](https://github.com/TranPhucVinh/C/tree/master/Application%20layer/HTTP/TCP)
* [Signal](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Signal)

# API

[API.md](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/API.md)

# Examples

### fork

* [fork examples](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/fork%20examples.md)
* Using pipe to communicate between parent and child process: [pipe examples](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/pipe%20examples.md)
* Using FIFO to communicate between 2 process: [FIFO example in File IO](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/FIFO.md#example-2)
