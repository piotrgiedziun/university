.extern printf
.global c_function
.section .data
val_text: .ascii "Hello form asm file\n"

.section .text
c_function:

push %ebp
mov %esp, %ebp

push $val_text
call printf

mov %ebp, %esp
pop %ebp
mov %ebx, %eax
ret
