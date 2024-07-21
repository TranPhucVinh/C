![](../../Environment/Images/process-memory-layout.png)

A process also has its environment which comes with environment variables. The startup routine takes the command line arguments, environment etc from the kernel and passes these on to the ``main()`` function.

* The command line arguments and the environment variables are stored at the top of the process memory layout at the higher addresses.
* [Stack segment](#stack-segment) is the memory area which is used by the process to **store the local variables of functions** and **other information that is saved every time a function is called**. This other information includes the return address ie the address from where the function was called, some information on the callers environment like its machine registers etc are stored on stack. Also worth mentioning here is that each time a recursive function is called a new stack frame is generated so that the each set of local variables does not interfere with any other set.
* **Heap segment** is the one which is used for dynamic memory allocation. This segment is not limited to a single process, instead it is shared among all the processes running in the system. Any process could dynamically allocate memory from this segment. Since this segment is shared across the processes so memory from this segment should be used cautiously and should be deallocated as soon as the process is done using that memory. **Forgetting deallocating memory in HEAP segment causes Memory leak**.
* All the **global** and **static variable** which **are not initialized** or **initiliazed with 0** are stored in the **BSS** segment (**Block Started by Symbol**). Upon execution, all the uninitialized global variables are initialized with the value zero.

E.g:

```c
int global;
int function_name(){
    static int static_variable = 0;
    return 0;
}
```

``global`` (uninitialized) and ``static_variable`` (initialized with ``0``) are then stored inside the ``DS``.

* All the **initialized global** and **static variables** are stored in the Ininitialized data segment also called Data segment (DS).

E.g:

```c
int global = 100;
int function_name(){
    static int static_variable = 1;
    return 0;
}
```

* **Text segment** is the memory area that contains the machine instructions that CPU executes. Usually, this segment is shared across different instances of the same program being executed. Since there is no point of changing the CPU instructions so this segment has ``read-only privileges``.

As seems from the figure above, the stack grows downwards while the heap grows upwards.

# Stack segment

All local variables of functions have their address unchanged on function calls:

```c
void func(){ 
    int a;
    int b;
    printf("%p %p\n", &a, &b);
} 

int main()
{
    func();//0x7fff193dd260 0x7fff193dd264
    func();//0x7fff193dd260 0x7fff193dd264; unchanged after the 1st call
}
```

That happens as the compiler might reuse the same address it had before.
# size

``size a.out``: displays the size of the text, initialized data, and uninitialized data (bss) segments of binary executable file ``a.out``
