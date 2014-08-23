# ASCII to NB v1
SYSEXIT  = 1
EXIT_SUCCESS = 0
INT_SIZE = 4

.data
.text
value: .ascii "123"

.global _start

_start: 
 movl $0, %ebx # current value
 movl $0, %eax # strore value
 movl $0, %ecx # loop couter
 movl $2, %edi # char count

while:
 movl $10, %ebx
 mull %ebx
 
 mov value(,%ecx, 1), %bl
 and $0xF, %bl
 add %ebx, %eax

 inc %ecx

 cmp %ecx, %edi
jnl while

# result in eax

koniec:
    mov $SYSEXIT, %eax
    mov $EXIT_SUCCESS, %ebx
    int $0x80
