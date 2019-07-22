## Compile

### Compile code C in sublime text, notepad, gedit,...

Shell

```shell
{
  "cmd" : ["gcc", "$file_name", "-o", "${file_base_name}", "-lm", "-Wall"],
  "selector" : "source.c",
  "shell":false,
  "working_dir" : "$file_path"
}
```

To run the code: cd to current c workspace:

then type: ``./<name of project>``

Reference: [How to Compile and Execute C/C++ Program On Ubuntu using Terminal Gedit, Sublime Text Editor](https://www.youtube.com/watch?v=QU8arxnpfhA)

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
  
## Library

**stdio.h:** standard io
