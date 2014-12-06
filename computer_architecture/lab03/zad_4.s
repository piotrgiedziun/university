.extern printf
.global run
.global addition

.section .data
text_value: .ascii "Example text value\n\0"
float_value: .float 1.23

.section .text

# funkcja uruchamiana z poziomu języka c
.type run, @function
run:

# ustawienie frame pointera
push %ebp
mov %esp, %ebp

# wywołanie bibliotecznej funkcji języka c
# printf("Example text value\n\0")
push $text_value # umieszczenie parametru na stosie
call printf # wywołanie funkcji

# wywołanie własnej funkcji zadeklarowanej w c
push $1
push float_value # parametr zmiennoprzecinkowy
call addition

# przywrócenie frame pointera
mov %ebp, %esp
pop %ebp
ret