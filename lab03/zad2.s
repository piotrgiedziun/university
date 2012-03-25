.global add

.section .text
add:

push %ebp
mov %esp, %ebp

mov 8(%ebp), %eax # a
mov 12(%ebp), %ebx # b

add %ebx, %eax 

mov %ebp, %esp
pop %ebp
ret
