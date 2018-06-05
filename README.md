# C

## Compile

### Compile code C in sublime text, notepad, gedit,...

follow this link:
[How to Compile and Execute C/C++ Program On Ubuntu using Terminal Gedit, Sublime Text Editor](https://www.youtube.com/watch?v=QU8arxnpfhA)

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

then type: ./<name of project>

### Compile C++, C on terminal

```shell
g++ -o output_file file.cpp
```
Then
``
./output_file
``

**Reference:** [Sublime text 3 - compile program and run in terminal](https://stackoverflow.com/questions/21196077/sublime-text-3-compile-program-and-run-in-terminal)

Format code: [Sublime Text 2 & 3 AStyle Formatter Plugin](https://packagecontrol.io/packages/SublimeAStyleFormatter)

Ctrl +alt +f
  
## Library

**stdio.h:** standard io
