GDB (which goes with ``gdb`` as its command) is a debugger for GCC.

# CLI

To run a program e.g ``a.out`` with ``gdb``, it must be first compiled with ``-g``: ``gcc -g test.c``

Then start GDB debugging for the output of that file: ``gdb a.out``. Terminal then will enter ``gdb`` CLI mode.

``gdb`` commands:

* ``run``: Run the program
* ``layout next``: Enter the current running program to start debugging each line with ``next``, ``step``, ...

Then type ``next`` to monitor. ``step`` to jump inside the function to monitor its variable.

**Notice**: Don't use ``printf()`` as it involve interrupt signal which conflict with signal used during gdb debugging.

# GUI

To use GDB in Visual Studio Code, check [Visual Studio Code document](Visual%20Studio%20Code.md).
