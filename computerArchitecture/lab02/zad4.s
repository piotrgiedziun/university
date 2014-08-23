# ASCII to NB v2
SYSEXIT  = 1
EXIT_SUCCESS = 0

.data
.lcomm tab, 32
.text
value: .ascii "123"

.global _start

_start: 

mov $SYSREAD, %eax 
mov $STDIN, %ebx 
mov $value, %ecx
mov $32, %edx 
int $0x80

 movl $0, %ebx # current value
 movl $0, %eax # strore value
 movl $0, %ecx
 movl $0xcc, %edi # char count

while:
 movl $10, %ebx
 mull %ebx
 
 mov value(,%ecx, 1), %bl
 cmp %ebx, %edi
 je koniec
 and $0xF, %bl
 add %ebx, %eax
 inc %ecx

jmp while


b: 
koniec:
    mov $SYSEXIT, %eax
    mov $EXIT_SUCCESS, %ebx
    int $0x80
