# Build the first C program

Organize a workspace folder for C source code with the following architecture:

```
|--main.c
|--WORKSPACE
|--BUILD
```

``main.c`` is the source code.

``WORKSPACE`` can be left empty as there is no specific requirement when we build this simple C program

``BUILD``:

```
cc_binary(
    name = "test_bazel",
    srcs = ["main.c"],
)
```

``cc_binary`` specifies for C/C++ source code. ``test_bazel`` is the build target.

To build: ``bazel build test_bazel``

If building successfully, the workspace architecture will be:

```
|--bazel-bin
|--bazel-C_workspace
|--bazel-out
|--bazel-testlogs
|--main.c
|--WORKSPACE
|--BUILD
```

To run the built program: ``bazel run test_bazel``
# Build a specific component

This architecture will help a project to have multiple components, in this case the component is ``main``:

```
|--main
|	|--main.c
|	|--BUILD
|--WORKSPACE
```

``BUILD`` and ``main.c`` are kept like above.

Build component ``main``: ``bazel build //main:test_bazel``

Run component ``main``: ``bazel run //main:test_bazel``

**Note**: Currently, in 9th September 2022, bazel is unable to build if it is inside a path with space like ``~/home/username/Work in progress$`` 

# Build with header files and library

```sh
|--main.c
|--head.c
|--head.h
|--WORKSPACE
|--BUILD
```

Now change ``BUILD`` file to:

```sh
cc_library(
    name = "library_name",
    srcs = ["head.c"],
    hdrs = ["head.h"],
)

cc_binary(
    name = "test_bazel",
    srcs = ["main.c"],
    deps = [
        ":library_name",        
    ],
)
```

``main.c``, ``head.c`` and ``head.h`` are all defined in [GCC compiler: Build source file](https://github.com/TranPhucVinh/C/blob/master/Environment/GCC%20compiler.md#build-source-file)

To build: ``bazel build test_bazel``

To run: ``bazel run test_bazel``

**Note**: Although ``main.c`` has included ``head.h`` like below, ``BUILD`` script must have ``hdrs``. 

``main.c``

```c
#include <stdio.h>
#include "head.h"
```

Without ``hdrs``, there will be error:

```
main.c:1:18: fatal error: head.h: No such file or directory
 #include "head.h"
```

**Build with header files/library files inside specific folder**: Check [cJSON implementation in C](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/JSON/README.md) for that implementation.

``include`` keyword in ``BUILD`` file is used to include the general folder for ``include`` in C source code like ``#include "header.h``. With ``includes = ["cJSON-1.7.15"],`` in ``BUILD`` file, user can call ``#include "cJSON.h"`` instead of ``#include "cJSON-1.7.15/cJSON.h"``

# Read file when running bazel build

```sh
|--main.c
|--test.json
|--WORKSPACE
|--BUILD
```

In order to read file ``test.json`` in ``main.c`` when running bazel build source code, field ``data`` has to be added.

```
cc_binary(
    name = "test_bazel",
    srcs = ["main.c"],
    data = ["test.json"],
)
```

With file ``test.json`` inside folder ``file`` and ``BUILD`` file like this:

```
|--main.c
|--file
|	|--test.json
|--WORKSPACE
|--BUILD
```

```
cc_binary(
    name = "test_bazel",
    srcs = ["main.c"],
    data = ["file/test.json"],
)
```

Running the bazel build file will result in error:

```
Unable to open file test.json
```

**Problem solved**:

``BUILD`` in ``file``:

```
exports_files(["test.json"])
```

``BUILD`` in main workspace:

```
cc_binary(
    name = "test_bazel",
    srcs = ["main.c"],
    data = ["//file:test.json"],
)
```

To read ``test.json`` inside folder ``file``, the source code now need to change to:

```c
printf("%s\n", read_file("file/test.json"));
```

# Build external library

Build external library like ``pthread`` (``gcc main.c -lpthread``):

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
├── main.c
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
