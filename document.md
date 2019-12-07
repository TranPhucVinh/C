### Compile C++, C on terminal

```shell
g++ -o output_file file.cpp
```

In Linux

```
./output_file
```

In Windows

```
./output_file.exe
```

To compile with mupltiples header files

``g++ -o outputFile main.c other.c etc.c``

``g++ -o outputFile main.cpp other.cpp etc.cpp``

### Shell script to compile

Shell

```shell
{
  "cmd" : ["gcc", "$file_name", "-o", "${file_base_name}", "-lm", "-Wall"],
  "selector" : "source.c",
  "shell":false,
  "working_dir" : "$file_path"
}
```
