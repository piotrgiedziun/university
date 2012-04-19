.extern printf # funkcja stdio
.extern c_char
.extern c_printf_s

.global run
.section .data
val_text: .ascii "Hello form asm file\n\0"

.section .text
.type run, @function
run:

push %ebp
mov %esp, %ebp

# wyświetlenie zmiennej zadeklarowaniej z poziomu asm
push $val_text
call printf

# wyświetlenie zmiennej zadeklarowaniej z poziomu c 
mov $c_char, %eax
push (%eax)
call printf

mov %ebp, %esp
pop %ebp
ret
