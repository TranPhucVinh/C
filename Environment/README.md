# Environment for C programming

* [Bare metal vs OS-based applications](Build.md#fundamental-concepts)
* [Cross compiler](Build.md#cross-compiler)
* [Toolchain](Build.md#toolchain)
* [C program compilation process](Build.md#c-program-compilation-process)

# [GCC compiler](GCC%20compiler.md)
The **GNU Compiler Collection** (**GCC**) is a **compiler system** produced by the GNU Project supporting various programming languages. GCC is a key component of the GNU toolchain. With GCC installed, command **gcc** and **cc** are available.
* [Build source file and build flags](), [external linkage](GCC%20compiler.md#compile-with-multiple-files-when-there-is-no-header-file) when compiling multiple files with no header file
* [Linker flags](GCC%20compiler.md#linker-flags)
* [-I flag](GCC%20compiler.md#include-directory-of-header-files-with--i): Include directory of header files
* [Makefile for GCC](Makefile%20for%20GCC.md)
**Compilers developed from GCC**:
* With AVR, we have ``AVR-GCC`` is a part of GCC and support compiling C program for AVR microcontrollers.
* ESP8266 core includes an ``xtensa gcc toolchain``.
# G++ compiler

G++ compiler is best to use on CPP source code, instead of C. Refer to [CPP for its implementation](https://github.com/TranPhucVinh/Cplusplus/blob/master/README.md#g-compiler).

A ``C`` source code with ``CPP`` syntax can be compiled normally: ``g++ test.c``

``test.c``

```cpp
#include <iostream>

using namespace std;

int main(){
  cout << "hello cpp";
}
```

# Static library and shared library

* [Static library](Static%20library.md) 
* [Shared library](Shared%20library.md)

GCC assumes that all libraries start with ``lib`` and end with ``.so`` or ``.a`` (``.so ``is for shared object or shared libraries, and ``.a`` is for archive, or statically linked libraries).

# [Bazel for C](Bazel)
# [CMake for C](CMake)
# Visual Studio Code
## Build C source code

``Ctr+Shift+B`` will build a single file. Visual Studio Code will ask the user to choose which compiler to build the file.

For a script to build the file, put the file inside a folder. Then press ``Ctr+Shift+B`` and choose the ``detected task`` icon, ``Configure task`` will appear, press that icon and ``task.json`` will appear.

If saved ``tasks.json`` as default the press ``Ctr+Shift+B`` again, Visual Studio Code will still ask for the compiler option.

Change ``"group": "build"`` in ``tasks.json`` to the following fields for automotically build:

```json
"group": {
    "isDefault": true,
    "kind": "build"
}
```

## Debug with GDB

Check [the related document in GDB](GDB/Visual%20Studio%20Code.md) for implementation of GDB on Visual Studio Code.
# Linux environment

## Set up command from a C process

To make ``a.out`` file compiled from a C source code to be a system wide available command, put it inside ``/bin`` folder.

**Step 1**: Copy ``a.out`` to ``/bin``: ``sudo cp a.out /bin``

**Step 2**: Command ``a.out`` now is available, simply run ``a.out``. Command ``a.out`` will be available in the system as long as it is still inside ``/bin``.

For safety purpose when installing local software like this case, it is better to use [/usr/local/bin](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/File%20system/File%20hierarchy.md#usr) or [/usr/sbin](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Physical%20layer/File%20system/File%20hierarchy.md#usr) instead of ``/bin`` as files in ``/bin`` will be overwritten when the system software is updated.

Take all steps like above with ``/bin`` to set up the command:

**Step 1**: sudo cp a.out /usr/local/bin

**Step 2**: Command ``a.out`` now is available as long as it is still inside ``/usr/local/bin``.

**Linux Programmer's Manual**

Manual document for functions prototype can be accessed by ``man function_prototype``.

E.g: ``man scanf``

## nm

List symbols from object files

```sh
nm a.out
```
# [Images used in Github project](Images)
