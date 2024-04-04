#include "std/dflib.h"
#include "std/dfio.h"

void _start(void) {
    dfwrite(stdout, "Hello, World!\n", 14);
    dfexit(EXIT_SUCESS);
    __builtin_unreachable(); // make that the compiler doesn't put anything else
}
