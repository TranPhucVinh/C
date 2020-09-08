Run an embedded Shell script in ``C`` source code

```c
#include <stdlib.h>

main() {
	system("ls"); //Run ls command
}
```

On Windows, the ``a.exe`` of this file will run normally in Git Bash and will result in error ``command not found`` in Command Prompt.

``system("dir");`` will run properly in Command prompt.