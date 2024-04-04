#include "dfio.h"
#include "../syscall/x86_64.h"

int dfwrite(unsigned int fd, const char* buff, size_t count) {
    register int syscall_code asm(SYSCALL_REG) = SYS_WRITE;
    register unsigned int rfd asm(ARG_0) = fd;
    register const char* rbuff asm(ARG_1) = buff;
    register size_t rcount asm(ARG_2) = count;
    register int result asm(ARG_3);
    syscall;
    return result;
}
