.global Filter
.section .text

# funkcja uruchamiana z poziomu języka c
.type Filter, @functionrun:
Filter:

# ustawienie frame pointera
push %ebp
mov %esp, %ebp

# przywrócenie frame pointera
mov %ebp, %esp
pop %ebp
ret
