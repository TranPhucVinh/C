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