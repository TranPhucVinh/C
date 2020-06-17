### Compile C++, C on terminal with G++

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

### Compile C source code with GCC

``gcc main.c``

The compiled file will be ``a.out``

To compile with an external library ``gcc main.c -l<external-library-name>``

E.g: ``gcc httpClient.c -lcurl``

**GCC on Windows**:

For GCC build on Window, install ``TDM-GCC-64``.

### Shell script to compile

```shell
{
  "cmd" : ["gcc", "$file_name", "-o", "${file_base_name}", "-lm", "-Wall"],
  "selector" : "source.c",
  "shell":false,
  "working_dir" : "$file_path"
}
```