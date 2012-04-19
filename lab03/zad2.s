SYSWRITE = 4
STDOUT = 1

.global add
.global upper
.section .text
.lcomm tab, 32

# funkcja dodająca dwie wartości 
# zwracająca ich wynik
.type add, @function
add:

push %ebp
mov %esp, %ebp

mov 8(%ebp), %eax # a int
mov 12(%ebp), %ebx # b int

# wynik w eax - zwracana wartość
add %ebx, %eax 

mov %ebp, %esp
pop %ebp
ret

# funkcja zwiększająca pierwszy znak
.type upper, @function
upper:
push %ebp
mov %esp, %ebp

# pobranie argumentu
mov 8(%ebp), tab

# maska 11011111 zamienia na wielkie
mov $0xA80427, %eax	
#and %eax, (tab, 0, 1)

# wyświetla przetworzony string
mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov tab, %ecx
mov $32, %edx
int $0x80

mov %ebp, %esp
pop %ebp
ret