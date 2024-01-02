# Build with header files and library

```sh
├── main.c
├── header.c
├── header.h
├── WORKSPACE
└── BUILD
```

Now change ``BUILD`` file to:

```sh
cc_library(
    name = "library_name",
    srcs = ["header.c"],
    hdrs = ["header.h"],
)

cc_binary(
    name = "test_bazel",
    srcs = ["main.c"],
    deps = [
        ":library_name",        
    ],
)
```

``main.c``, ``header.c`` and ``header.h`` are all defined in [GCC compiler: Build source file](https://github.com/TranPhucVinh/C/blob/master/Environment/GCC%20compiler.md#build-source-file)

To build: ``bazel build test_bazel``

To run: ``bazel run test_bazel``

**Note**: Although ``main.c`` has included ``header.h`` like below, ``BUILD`` script must have ``hdrs``. 

``main.c``

```c
#include <stdio.h>
#include "header.h"
```

Without ``hdrs``, there will be error:

```
main.c:1:18: fatal error: header.h: No such file or directory
 #include "header.h"
```

**Build with header files/library files inside specific folder**: Check [cJSON implementation in C](https://github.com/TranPhucVinh/C/blob/master/Data%20structure/JSON/README.md) for that implementation.

``include`` keyword in ``BUILD`` file is used to include the general folder for ``include`` in C source code like ``#include "header.h``. With ``includes = ["cJSON-1.7.15"],`` in ``BUILD`` file, user can call ``#include "cJSON.h"`` instead of ``#include "cJSON-1.7.15/cJSON.h"``

# Build with external library

Build with external library like ``pthread`` (``gcc main.c -lpthread``):

```c
cc_binary(
    name = "main",
    srcs = ["main.c"],
    linkopts = ["-lpthread"],
)
```

For multiple external library, e.g ``-li2c``:

```
linkopts = ["-lpthread", "-li2c"],
```

# Static library

Include an existed static library ``.a`` to ``BUILD`` with ``cc_import()``

```c
cc_import(
	name = "library_name",
	hdrs = ["head.h"],
	static_library = "head.a",
)

cc_binary(
    name = "test_bazel",
    srcs = ["main.c"],
    deps = [":library_name"],
)
```

``main.c``

```c
#include "head.h"

int main(){
	display_string();//Function from head.a
}
```

For ``head.h`` inside ``include`` folder:

```sh
├── include
│   └── head.h
├── head.a
└── main.c
```

```sh
cc_import(
	name = "library_name",
	static_library = "head.a",
    hdrs = ["include/head.h"],
)

cc_binary(
    name = "test_bazel",
    srcs = ["main.c"],
    includes = ["include"],
    deps = [":library_name"],
)
```
