# Wildcard

```c
#include <fnmatch.h>
int fnmatch(const char *pattern, const char *string, int flags);
```
flags:
* **FNM_NOESCAPE**: treat backslash as an ordinary character, instead of an escape character.

```c
int ret = fnmatch("wh*", "what", FNM_NOESCAPE);// String matched
if (!ret){
    printf("String matched\n");
} else if (ret == FNM_NOMATCH){
    printf("String not matched\n");
}

ret = fnmatch("wh*", "a while", FNM_NOESCAPE);// String not matched
if (!ret){
    printf("String matched\n");
} else if (ret == FNM_NOMATCH){
    printf("String not matched\n");
}
```