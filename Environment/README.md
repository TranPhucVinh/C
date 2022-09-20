# Software development environment

## Build process

Check [Build document](Build.md)

## GCC compiler

Check [GCC compiler document](GCC%20compiler.md)

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
