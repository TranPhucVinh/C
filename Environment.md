## GCC compiler

GCC is a compiler system that supporting various programming languages.

``gcc -S main.c``: Build C source code (High level language) to assembly code, the output file will be ``main.s``

``gcc -o main main.c``: Specify the executable output file as ``main``

``gcc main.c``: Compile, assemble and link source file ``main.c`` into ``a.exe`` (Windows) or ``a.out`` (Unix)

### For object file

``gcc -c main.c``: Compile and assemble ``main.c`` into an object file ``main.o``.

**Notice**: Only a ``.c`` file result in a ``.o`` file

``gcc -c test1.c test2.c`` results in ``test.o`` and ``test1.o``.

**Notice**: Cannot specify -o with -c, -S or -E with multiple files

``gcc -c test.c test1.c -o test.o`` will be error

``test.c`` and ``test1.c`` have to be compiled seperatedly for ``test.o`` and ``test1.o``

### External library

To compile with an external library ``gcc main.c -l<external-library-name>``

E.g: ``gcc httpClient.c -lcurl``

To compile with mupltiples header files

``gcc -o outputFile main.c other.c etc.c``

### GCC on Windows

For GCC build on Windows, install ``TDM-GCC-64``.

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

### Shell script to compile

```shell
{
  "cmd" : ["gcc", "$file_name", "-o", "${file_base_name}", "-lm", "-Wall"],
  "selector" : "source.c",
  "shell":false,
  "working_dir" : "$file_path"
}
```
