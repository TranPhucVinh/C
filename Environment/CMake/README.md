**CMake** is an open-source, cross-platform family of tools designed to build, test and package software.

# Install

CMake can be installed with ``sudo apt install cmake`` or installed with the tar file.

For installing with tar file, install ``cmake-3.23.0.tar.gz`` file from CMake webpage then extract to folder ``cmake-3.23.0``.

Inside folder ``cmake-3.23.0``, run file ``./bootstrap`` to setup CMake.

After successfully setup CMake, command ``cmake`` will be available. Folder ``cmake-3.23.0`` can then be deleted.
# API

## register_component()

For each component, CMakeLists file calls ``register_component``, which calls the CMake ``add_library`` function to add a library and then adds source files, compile options, etc.

## set()

```cmake
set(<variable> <value>... [PARENT_SCOPE])
```

Set the given ``variable`` in the current function or directory scope. E.g

```cmake
# Set the source file
set(SRC_FILE header.c)

# Set the header file
set(HEADER_FILE header.h)
```
