### Linux Programmer's Manual

Manual document for functions prototype can be accessed by ``man function_prototype``.

E.g: ``man scanf``

### Shell script to compile

```shell
{
  "cmd" : ["gcc", "$file_name", "-o", "${file_base_name}", "-lm", "-Wall"],
  "selector" : "source.c"
  "shell":false,
  "working_dir" : "$file_path"
}
```
