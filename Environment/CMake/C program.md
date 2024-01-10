# Build a single C program

Set up a working folder for CMake project like ``c_make_test``:

```sh
c_make_test
|--main.c
|--CMakeLists.txt
```

``CMakeLists.txt``

```CMake
# cmake_minimum_required(VERSION 3.10)

# set the project name
project(test_c_make)

# add the executable
add_executable(test_c_make main.c)
```

Project's name can be used with ``${PROJECT_NAME}``:

```CMake
# set the project name
project(CMake_for_C_src_code)

# add the executable
add_executable(${PROJECT_NAME} main.c) # ${PROJECT_NAME} will get the PROJECT_NAME setup previously from project()
```

Inside ``c_make_test``, run ``cmake .`` or in the same location with ``c_make_test``, run ``cmake c_make_test/``:

```sh
username@hostname:~/wip/c_make_test$ cmake .
```
If building inside ``c_make_test``, the folder now will include:

```
username@hostname:~/wip/c_make_test$ ls
CMakeFiles
c_make_test
CMakeCache.txt
cmake_install.cmake
Makefile
```

Still inside ``c_make_test``, run: ``make``, binary file ``test_c_make`` will be created. Then run ``test_c_make`` to run the C program.
```sh
username@hostname:~/wip/c_make_test$ make
# test_c_make is created
username@hostname:~/wip/c_make_test$ ./test_c_make
```
Specify the build output to ``c_workspace_cmake`` folder by ``-B`` flag: ``cmake c_make_test/ -B c_workspace_cmake/``

If there is error with the source file, running ``cmake c_make_test/`` will still be fine then run ``make`` will have error.

# Build the program with source files

```
|--main.c
|--header.c
|--header.h
|--CMakeLists.txt
```

```CMake
project(test_c_make)

# add the executable
add_executable(${PROJECT_NAME} main.c header.c)
```

``main.c`` then just simply includes ``header.h``:

```c
#include "header.h"
//Operations go here
```
# Library with add_library()
**Creating library with add_library()**:

With files architecture like above:

```CMake
# set the project name
project(test_c_make)

# add the executable
add_executable(${PROJECT_NAME} main.c)

add_library(
    header
    header.h
    header.c)

target_link_libraries(${PROJECT_NAME} PRIVATE header)
```

``add_library()``: Default for ``add_library()`` is to build static library. So when running the ``CMakeLists.txt`` above, there will be:

```
[ 50%] Linking C static library libheader.a
```

Other library types can be specified like ``SHARED``, ``STATIC``, ``MODULE``.
# cmake --build for static library
```sh
c_make_test
|--main.c
|--CMakeLists.txt
|--header_lib
    |--header.c
    |--header.h
    |--CMakeLists.txt
```

``cmake --build`` helps build binary library, like static and dynamic library.

``CMakeLists.txt`` inside ``header_lib``
```CMake
cmake_minimum_required(VERSION 3.12)
project(static_library)

# Set the source file
set(SRC_FILE header.c)

# Set the header file
set(HEADER_FILE header.h)

# Create the static library
add_library(headerlib STATIC ${SRC_FILE} ${HEADER_FILE})
```
Build the static lib inside ``header_lib``
```sh
username@hostname:~/wip/c_make_test/header_lib$ cmake .
username@hostname:~/wip/c_make_test/header_lib$ cmake --build . # This will generate libheaderlib.a
```
Main ``CMakeLists.txt`` inside ``c_make_test``
```CMake
cmake_minimum_required(VERSION 3.12)
project(MAIN_SRC)

# Set the source files for the main executable
set(MAIN_SOURCE main.c)

# Set the header files
set(HEADER_FILES header_lib/header.h)

# Set the library directory
set(LIBRARY_DIR header_lib)

# Set the name of your static library
set(LIB_NAME headerlib)

# Add the static library
add_library(${LIB_NAME} STATIC IMPORTED)
set_target_properties(${LIB_NAME} PROPERTIES IMPORTED_LOCATION ${LIBRARY_DIR}/lib${LIB_NAME}.a)

# Create the executable and link with the static library
add_executable(main_src ${MAIN_SOURCE} ${HEADER_FILES}) # main_src is the main program to be built into
target_link_libraries(main_src ${LIB_NAME})

# Set include directories
target_include_directories(main_src PRIVATE header_lib)
```
Then build and run the main source:
```sh
username@hostname:~/wip/c_make_test$ cmake .
username@hostname:~/wip/c_make_test$ cmake --build . # This will build target main_src (main program to be built)
username@hostname:~/wip/c_make_test$ ./main_src # Run main_src
```
# Cross compiler
Add flag ``CMAKE_C_COMPILER`` for the cross compiler location:
```CMake
# cmake_minimum_required(VERSION 3.10)

# set the project name
project(test_c_make)

set(CMAKE_C_COMPILER /bin/aarch64-linux-gnu-gcc)

# add the executable
add_executable(${PROJECT_NAME} main.c)
```
