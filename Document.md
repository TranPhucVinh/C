### GCC compiler

GCC is a compiler system that supporting various programming languages.

``gcc -S main.c``: Build C source code (High level language) to assembly code, the output file will be ``main.s``

``gcc -c main.c``: Compile and assemble ``main.c`` into an object file ``main.o``

``gcc main.c``: Compile, assemble and link source file ``main.c`` into ``a.exe`` (Windows) or ``a.out`` (Unix)

``gcc -o main main.c``: Specify the executable output file as ``main``

To compile with an external library ``gcc main.c -l<external-library-name>``

E.g: ``gcc httpClient.c -lcurl``

To compile with mupltiples header files

``gcc -o outputFile main.c other.c etc.c``

**GCC on Windows**:

For GCC build on Windows, install ``TDM-GCC-64``.

### G++ compiler

```shell
g++ -o output_file file.cpp
```

In Linux: ``./output_file``

In Windows: ``./output_file.exe``

To compile with mupltiples header files

``g++ -o outputFile main.c other.c etc.c``

``g++ -o outputFile main.cpp other.cpp etc.cpp``

A ``.c`` source code with ``CPP`` syntax can be compiled normally:

**Example**:

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