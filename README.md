# cdflib

Try to rewrite some of the functions of the C standard library in order to have
a better understanding of how works under the hood. The code uses `asm`
statement to perform syscalls and the code is not linked to the standard library
(`nostdlib` option).

## asm

- The documentation can be found [here](https://gcc.gnu.org/onlinedocs/gcc/extensions-to-the-c-language-family/how-to-use-inline-assembly-language-in-c-code.html).
- The list of kernel syscalls can be found [here](https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md).

### sysexit example (x86)

#### using only asm

```c
void sys_exit(int code) {
    asm(
        "movl $1,%eax;" // set eax = 1 (exit syscall in x86)
        "movl $0,%ebx;" // set ebx = 0 (0 exit code)
        "int 0x80" // interrupt and execute syscall (x86)
    )
}
```

#### using input and output

```c
void sys_exit(int code) {
    asm(
        "int 0x80" // interrupt and execute syscall (x86)
        : // no output
        : "a" (1), "b" (0) // set eax = 1 (exit syscall in x86)
                           // and ebx = 0 (0 exit code)
    )
}
```

### using register variables

```c
void sys_exit(int code) {
    register int syscall_code asm("eax") = 0x01;
    register int output asm("ebx") = code;
    asm("int 0x80")
}
```

### write example (x86_64)

Here is an example for the `x86_64` architecture. The write syscall takes 3
arguments, the file descriptor (`1` for `stdout` for instance), the buffer to
write and the size of the buffer. The result of the syscall is store in the
`rax` register.

**WARNING**: in the previous example we were using `x86` architecture (32 bits)
so `0x01` corresponded to the `sys_exit` syscall. Here we are using `x86_64` so
`0x01` corresponds to the `write` syscall (`sys_exit` is 60 so `0x3c`).
Moreover, the interruption can be done using `syscall` instead of `int 0x80`.

```c
int dfwrite(unsigned int fd, const char* buff, size_t count) {
  register int          syscall_code asm("rax") = 0x01;
  register unsigned int rfd asm("rdi") = fd;
  register const char  *rbuff asm("rsi") = buff;
  register size_t       rcount asm("rdx") = count;
  register int          result asm("rax");
  asm("syscall");
  return result;
}
```
