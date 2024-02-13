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
# Regular expression

Create/Compile a regular expression pointer
```c
#include <regex.h>
int regcomp(&regex, expression, flag)
```
 
* **regex**: pointer to a memory location where expression is matched and stored
* **expression**: The regular expression pattern, e.g [a-zA-z] is a string type
flag to specify the type of compilation
* **flag**: Set 0 for no flag

```c
int regexec(const regex_t *regex, const char *string, size_t nmatch, regmatch_t *pmatch, int eflags);
```
* **regex**: The regex pointer created by **regcomp()**
* **string**: The string to searched by **regex**
* **nmatch** is the number of substrings in string that **regexec()** function should try to match with subexpressions in **regex**. The array you supply for **pmatch** must have at least **nmatch** elements.
* **eflags**: defines customizable behavior of the **regexec()** function

```c
#include <stdio.h>
#include <regex.h>

#define REGEX_PATTERN  "ab*c"
#define NO_FLAG			0 // Set 0 for no flag in regcomp()

#define NMATCH	0
#define PMATCH	NULL
#define EFLAGS	0

int main()
{
	regex_t regex;

	if (!regcomp(&regex, REGEX_PATTERN, NO_FLAG)){
		int ret = regexec(&regex, "abbc", NMATCH, PMATCH, EFLAGS);
		if (!ret){
			printf("Pattern found\n");
		} else if (ret == REG_NOMATCH) printf("Pattern not found\n");
	} else {
		printf("Comilation error for regex; unable to create regex\n");
	}
	return 0;
}
```