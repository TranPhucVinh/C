Bare metal application

![](../Environment/Images/bare_mental_application.PNG)

OS-based application

![](../Environment/Images/os_based_application.PNG)

# GCC compilation process

![](../Environment/Images/gcc_compilation_process.png)

**Preprocessor**

Before compilation, preprocessor takes the source code and perform operation:
* Remove new line, space, comment
* Include header file

**Compilation**: Build the output from preprocessor to assembly code (``.s``)

**Assemble**: Compile assembly code to machine language (0 and 1). ``.o`` or ``.obj`` file will then output, those files (e.g ``main.o``) are all binary files.