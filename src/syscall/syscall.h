#ifndef SYSCALL_H
#define SYSCALL_H

#if defined(__x86_64__)
#include "x86_64.h"
#elif defined(__x86__)
#include "x86.h"
#endif

#endif
