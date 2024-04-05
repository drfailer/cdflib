#include "dfio.h"
#include "../syscall/syscall.h"
#include "string.h"

int dfwrite(unsigned int fd, const char *buff, size_t count) {
    register int syscall_code asm(SYSCALL_REG) = SYS_WRITE;
    register unsigned int rfd asm(ARG_0) = fd;
    register const char *rbuff asm(ARG_1) = buff;
    register size_t rcount asm(ARG_2) = count;
    register int result asm(SYSCALL_OUT_REG);
    syscall;
    return result;
}

int dfread(unsigned int fd, char *buff, size_t count) {
    register int syscall_code asm(SYSCALL_REG) = SYS_READ;
    register unsigned int rfd asm(ARG_0) = fd;
    register const char *rbuff asm(ARG_1) = buff;
    register size_t rcount asm(ARG_2) = count;
    register int result asm(SYSCALL_OUT_REG);
    syscall;
    return result;
}

/******************************************************************************/
/*                                  dfprintf                                  */
/******************************************************************************/

/*
 * This function has to be here in order to be able to use variadic arguments.
 */
void __stack_chk_fail(void) {
    char msg[] = "Error: stack overflow.\n";
    dfwrite(stderr, msg, sizeof(msg));
}

/*
 * Basic implementation of vprintf. Here we have to add `char* dest` as we don't
 * have an implementation of `FILE` that could allow to use a string buffer as a
 * file.
 *
 * BUG: __builtin_va_list doesn't work with floats and doubles.
 */
int dfvprintf_impl(unsigned int fd, char *dest, size_t destsize,
                   const char *restrict fmt, __builtin_va_list lst,
                   unsigned char mode) {
    char buff[1024];
    long l;
    double d;
    char *str;

    if (mode == BUFFER_MODE && dest) {
        dest[0] = 0;
        destsize--;
    }

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
            case 'd':
                l = __builtin_va_arg(lst, long);
                dflongtostr(buff, l, 1024);
                break;
            case 'f':
                d = __builtin_va_arg(lst, double);
                dfdoubletostr(buff, d, 1000, 10e15);
                break;
            case 'c':
                buff[0] = (char)__builtin_va_arg(lst, int);
                buff[1] = 0;
                break;
            case 's':
                str = __builtin_va_arg(lst, char *);
                dfstrcpy(buff, str);
                break;
            default:
                buff[0] = *fmt;
                buff[1] = 0;
                break;
            }
        } else {
            buff[0] = *fmt;
            buff[1] = 0;
        }
        if (mode == FILE_MODE) {
            if (dfwrite(fd, buff, dfstrlen(buff)) == -1) {
                return -1;
            }
        } else if (mode == BUFFER_MODE && dest && destsize > 0) {
            dfstrncpy(dest, buff, destsize);
            dest += dfstrlen(dest);
            destsize -= dfstrlen(buff);
        } else {
            return -1;
        }
        fmt++;
    }

    if (mode == BUFFER_MODE && dest) {
        *dest = 0;
    }
    return 0;
}

int dffprintf(unsigned int fd, const char *restrict fmt, ...) {
    __builtin_va_list lst;
    int result;

    __builtin_va_start(lst, fmt);
    result = dfvprintf_impl(fd, NULL, 0, fmt, lst, FILE_MODE);
    __builtin_va_end(lst);
    return result;
}

int dfprintf(const char *restrict fmt, ...) {
    __builtin_va_list lst;
    int result;

    __builtin_va_start(lst, fmt);
    result = dfvprintf_impl(stdout, NULL, 0, fmt, lst, FILE_MODE);
    __builtin_va_end(lst);
    return result;
}

int dfsprintf(char *dest, size_t size, const char *restrict fmt, ...) {
    __builtin_va_list lst;
    int result;

    __builtin_va_start(lst, fmt);
    result = dfvprintf_impl(stdout, dest, size, fmt, lst, BUFFER_MODE);
    __builtin_va_end(lst);
    return result;
}
