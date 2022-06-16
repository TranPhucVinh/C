# Software development environment

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
# Github project environment

[Images used in that projects](Images)
