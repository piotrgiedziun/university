SYSEXIT = 1
EXIT_SUCCESS = 0

.global _start

.section .text

_start:
						
mov $0, %edx
mov $16, %eax
mov $1, %ecx

mul %ecx
imul %ecx
div %ecx
idiv %ecx

mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
