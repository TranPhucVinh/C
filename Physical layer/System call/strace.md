``strace`` for ``a.out`` program of a simple ``printf()`` program:

```c
#include <stdio.h>

int main(){
    printf("Hello \n");
}
```

Run ``strace ./a.out``

**Result**

```
execve("./a.out", ["./a.out"], [/* 74 vars */]) = 0
brk(NULL)                               = 0x1505000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=133990, ...}) = 0
mmap(NULL, 133990, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f97ba51a000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0`\t\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1868984, ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f97ba519000
mmap(NULL, 3971488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f97b9f4c000
mprotect(0x7f97ba10c000, 2097152, PROT_NONE) = 0
mmap(0x7f97ba30c000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1c0000) = 0x7f97ba30c000
mmap(0x7f97ba312000, 14752, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f97ba312000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f97ba518000
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f97ba517000
arch_prctl(ARCH_SET_FS, 0x7f97ba518700) = 0
mprotect(0x7f97ba30c000, 16384, PROT_READ) = 0
mprotect(0x600000, 4096, PROT_READ)     = 0
mprotect(0x7f97ba53b000, 4096, PROT_READ) = 0
munmap(0x7f97ba51a000, 133990)          = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 2), ...}) = 0
brk(NULL)                               = 0x1505000
brk(0x1526000)                          = 0x1526000
write(1, "Hello \n", 7Hello 
)                 = 7
exit_group(0)                           = ?
+++ exited with 0 +++
```