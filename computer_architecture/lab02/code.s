SYSEXIT  = 1
SYSREAD = 3
EXIT_SUCCESS = 0

.global _start

_start:

koniec:
    mov $SYSEXIT, %eax
    mov $EXIT_SUCCESS, %ebx
    int $0x80
