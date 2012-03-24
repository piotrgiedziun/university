.extern printf
.extern c_char
.extern c_printf_s

.global c_function
.section .data
val_text: .ascii "Hello form asm file\n"

.section .text
c_function:

push %ebp
mov %esp, %ebp

push $val_text
call printf

mov $c_char, %eax
push (%eax)
call printf

mov %ebp, %esp
pop %ebp
ret
