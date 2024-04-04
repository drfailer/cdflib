#include "std/dflib.h"
#include "std/dfio.h"

void _start(void) {
    char buff[100] = {0};
    dfwrite(stdout, "Enter a message:\n", 17);
    dfread(stdin, buff, 100);
    dfwrite(stdout, buff, 100);
    dfexit(EXIT_SUCESS);
    __builtin_unreachable(); // make that the compiler doesn't put anything else
}
