``Ctr+Shift+B`` will build a single file. Visual Studio Code will ask the user to choose which compiler to build the file.

For a script to build the file, put the file inside a folder. Then press ``Ctr+Shift+B`` and choose the ``detected task`` icon, ``Configure task`` will appear, press that icon and ``task.json`` will appear.

If saved ``tasks.json`` as default the press ``Ctr+Shift+B`` again, Visual Studio Code will still ask for the compiler option.

Change ``"group": "build"`` in ``tasks.json`` to the following fields for automotically build:

```json
"group": {
    "isDefault": true,
    "kind": "build"
}
```