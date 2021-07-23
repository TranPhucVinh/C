Install ``gdb`` for debugging for C and C++

### Windows

Set up debug environment, which finally result in ``launch.json`` file.

``launch.json``

```c
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/a.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:\\TDM-GCC-64\\bin\\gdb.exe", //add/update path to gdb
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

### Linux

If ``launch.json`` is not found, create ``launch.json`` in ``.vscode`` then button ``Add configuration`` will automatic appear to automatically generate configurations information 

```json
{
    "configurations": [
    {
        "name": "(gdb) Attach",
        "type": "cppdbg",
        "request": "attach",
        "program": "${workspaceFolder}/a.out",
        "processId": "${command:pickProcess}",
        "MIMode": "gdb",
        "setupCommands": [
            {
                "description": "Enable pretty-printing for gdb",
                "text": "-enable-pretty-printing",
                "ignoreFailures": true
            }
        ]
    }
    ]
}
```

This ``launch.json`` file is quite difficult as it require user to choose the procesID of the current running terminal for debugging

To make things easier, use ``launch.json`` config from Windows like above but remove ``"miDebuggerPath": "C:\\TDM-GCC-64\\bin\\gdb.exe", //add/update path to gdb``

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/main",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: gcc build active file"
        }
    ]
}
```
After setting ``launch.json``, add breakpoints and runs the debug icon of Visual Studio Code.
