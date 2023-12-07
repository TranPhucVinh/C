# Software development environment

* Bare metal vs OS-based applications
* [Cross compiler](Build.md#cross-compiler)
* [Toolchain](Build.md#toolchain)
* [C program compilation process](Build.md#c-program-compilation-process)

## [GCC compiler](GCC%20compiler.md)

## G++ compiler

```shell
g++ -o output_file file.cpp
```

In Linux: ``./output_file``

In Windows: ``./output_file.exe``

To compile with mupltiples header files

``g++ -o outputFile main.c other.c etc.c``

``g++ -o outputFile main.cpp other.cpp etc.cpp``

A ``C`` source code with ``CPP`` syntax can be compiled normally: ``g++ test.c``

``test.c``

```cpp
#include <iostream>

using namespace std;

int main(){
  cout << "hello cpp";
}
```

A ``C`` source file can be compiled normally with other ``CPP`` header files: ``g++ main.c test.cpp``

## Static library and shared library

* [Static library](Static%20library.md) 
* [Shared library](Shared%20library.md)

GCC assumes that all libraries start with ``lib`` and end with ``.so`` or ``.a`` (``.so ``is for shared object or shared libraries, and ``.a`` is for archive, or statically linked libraries).

## Linux environment

### Set up command from a C process

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

### nm

List symbols from object files

```sh
nm a.out
```

# Github project environment

[Images used in that projects](Images)
