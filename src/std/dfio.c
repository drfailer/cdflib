#include "dfio.h"
#include "string.h"
#include "../syscall/syscall.h"

int dfwrite(unsigned int fd, const char* buff, size_t count) {
    register int syscall_code asm(SYSCALL_REG) = SYS_WRITE;
    register unsigned int rfd asm(ARG_0) = fd;
    register const char* rbuff asm(ARG_1) = buff;
    register size_t rcount asm(ARG_2) = count;
    register int result asm(SYSCALL_OUT_REG);
    syscall;
    return result;
}

int dfread(unsigned int fd, char* buff, size_t count) {
    register int syscall_code asm(SYSCALL_REG) = SYS_READ;
    register unsigned int rfd asm(ARG_0) = fd;
    register const char* rbuff asm(ARG_1) = buff;
    register size_t rcount asm(ARG_2) = count;
    register int result asm(SYSCALL_OUT_REG);
    syscall;
    return result;
}

/******************************************************************************/
/*                                  dfprintf                                  */
/******************************************************************************/

void __stack_chk_fail(void) {
    dfwrite(stderr, "Error: stack overflow.\n", 23);
}

int dffprintf(unsigned int fd, const char *fmt, ...) {
    __builtin_va_list lst;
    char buff[1024];
    long l;
    double d;
    char *str;

    __builtin_va_start(lst, fmt);
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
            case 'd':
                l = __builtin_va_arg(lst, long);
                dflongtostr(buff, l, 1024);
                dfwrite(fd, buff, dfstrlen(buff));
                break;
            case 'f':
                d = __builtin_va_arg(lst, double);
                dfdoubletostr(buff, d, 1000, 10e15);
                dfwrite(fd, buff, dfstrlen(buff));
                break;
            case 'c':
                buff[0] = (char) __builtin_va_arg(lst, int);
                dfwrite(fd, buff, 1);
                break;
            case 's':
                str = __builtin_va_arg(lst, char*);
                dfwrite(fd, str, dfstrlen(str));
                break;
            default:
                dfwrite(fd, fmt, 1);
                break;
            }
        } else {
            dfwrite(fd, fmt, 1);
        }
        fmt++;
    }
    __builtin_va_end(lst);
    return 0;
}
