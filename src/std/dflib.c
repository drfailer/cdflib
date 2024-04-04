#include "dflib.h"
#include "../syscall/x86_64.h"

void dfexit(int code) {
    register int syscall_code asm("rax") = SYS_EXIT;
    register int output asm("rdi") = code;
    syscall;
}

