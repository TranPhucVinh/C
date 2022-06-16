# Software development environment in this repository

Main OS: Ubuntu 16.04

Other OS:
* Windows (specifically noted on any software that are built on Windows)
* WSL Unbuntu 18.04

## Fundamental concepts

Bare metal application

![](../Environment/Images/bare_mental_application.PNG)

OS-based application

![](../Environment/Images/os_based_application.PNG)

## Linux environment

**Linux Programmer's Manual**

Manual document for functions prototype can be accessed by ``man function_prototype``.

E.g: ``man scanf``

### nm

List symbols from object files

```sh
nm a.out
```

### Shell script to compile

```shell
{
  "cmd" : ["gcc", "$file_name", "-o", "${file_base_name}", "-lm", "-Wall"],
  "selector" : "source.c"
  "shell":false,
  "working_dir" : "$file_path"
}
```
