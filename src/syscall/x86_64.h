#ifndef X86_64
#define X86_64

#define SYS_EXIT 0x3c
#define SYS_READ 0x00
#define SYS_WRITE 0x01

#define rax "rax"
#define ARG_0 "rdi"
#define ARG_1 "rsi"
#define ARG_2 "rdx"
#define ARG_3 "r10"
#define ARG_4 "r8"
#define ARG_5 "r9"

#define syscall asm("syscall")

#endif

