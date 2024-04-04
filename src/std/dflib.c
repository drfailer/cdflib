#include "dflib.h"
#include "../syscall/syscall.h"

void dfexit(int code) {
    register int syscall_code asm(SYSCALL_REG) = SYS_EXIT;
    register int output asm(ARG_0) = code;
    syscall;
}

void* dfmemset(void *str, int value, size_t count) {
    int *ptr = (int*) str;
    while (count--) {
        *ptr++ = value;
    }
    return str;
}
