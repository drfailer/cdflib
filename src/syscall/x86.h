#ifndef X86
#define X86

#define SYS_EXIT 0x01
#define SYS_READ 0x03
#define SYS_WRITE 0x04

#define SYSCALL_REG "eax"
#define SYSCALL_OUT_REG "eax"
#define ARG_0 "ebx"
#define ARG_1 "ecx"
#define ARG_2 "edx"
#define ARG_3 "esi"
#define ARG_4 "edi"
#define ARG_5 "edp"

#define syscall asm("int $0x80")

#endif
