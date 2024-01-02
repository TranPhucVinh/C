[Bazel](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Bash%20script/Build%20automation%20tools/Bazel.md) is an open-source build and test tool similar to Make, Maven, and Gradle. Bazel is multi-platform. It runs on Linux, macOS, and Windows.

Bazel doesn't support build folder to have space like ``~/home/username/Work in progress$``

# Build the first C program

Organize a workspace folder for C source code with the following architecture:

```
├── main.c
├── WORKSPACE
└── BUILD
```

``main.c`` is the source code.

``WORKSPACE`` can be left empty as there is no specific requirement when we build this simple C program

``BUILD``:

```sh
cc_binary(
    name = "test_bazel",
    srcs = ["main.c"],
)
```

``cc_binary`` specifies for C/C++ source code. ``test_bazel`` is the build target.

To build: ``bazel build test_bazel`` or ``bazel build //:test_bazel``

If building successfully, the workspace architecture will be:

```
├── bazel-bin
├── bazel-C_workspace
├── bazel-out
├── bazel-testlogs
├── main.c
├── WORKSPACE
└── BUILD
```

To run the built program: ``bazel run test_bazel`` or ``bazel run //:test_bazel``

File ``BUILD`` and ``WORKSPACE`` can also be named **BUILD.bazel** and **WORKSPACE.bazel** so that they won't be confused with other source codes.

**BUILD** is for Bazel target, while the empty **WORKSPACE** file is to build the source code.
# Build a single component

This architecture will help a project to have multiple components, in this case the component is ``main``:

```
├──main
|	├──main.c
|	└──BUILD
└── WORKSPACE
```

``BUILD`` and ``main.c`` are kept like above.

Build component ``main``: ``bazel build //main:test_bazel``

Run component ``main``: ``bazel run //main:test_bazel``

# Build multiple components
```
├──repo_1
|	├──main.c
|	└── BUILD
├──repo_2
|	├──main.c
|	└── BUILD
└── WORKSPACE
```
Build all those 2 components: ``bazel build //...``

Run each of those component: ``bazel run repo_1`` and ``bazel run repo_2``
# Read file when running bazel build

```sh
├── main.c
├── test.json
├── WORKSPACE
└── BUILD
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
├── main.c
├── file
|	  └── test.json
├── WORKSPACE
└── BUILD
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

``BUILD`` of ``file`` folder:

```
exports_files(["test.json"])
```

``BUILD`` inside main workspace:

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
