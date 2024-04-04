#ifndef X86
#define X86

#define SYS_EXIT 0x01
#define SYS_READ 0x03
#define SYS_WRITE 0x04

#define stdin 0
#define stdout 1
#define stderr 2

#define syscall asm("int $0x80")

typedef long unsigned int size_t;

#endif
