#include "x86_64.h"

void dfexit(int code) {
    register int syscall_code asm("rax") = SYS_EXIT;
    register int output asm("rdi") = code;
    syscall;
}

int dfwrite(unsigned int fd, const char* buff, size_t count) {
    register int syscall_code asm(rax) = SYS_WRITE;
    register unsigned int rfd asm(ARG_0) = fd;
    register const char* rbuff asm(ARG_1) = buff;
    register size_t rcount asm(ARG_2) = count;
    register int result asm(ARG_3);
    syscall;
    return result;
}

void _start(void) {
    dfexit(dfwrite(stdout, "hello\n", 6));
    /* dfexit(0); */
    __builtin_unreachable();
}
