.align 32
.extern input
.extern input2
.extern output
.global asm_div
.global asm_add

.section .text

# funkcja dzieląca liczby zmiennoprzecinkowe
.type asm_div, @function    
asm_div:       
    push %ebp
    mov %esp,%ebp

    finit
    fld input
    fld input2
    fxch # st(1) <-> st(0) forma zapisu a/b a nie b/a
    fdiv %st(1), %st(0) # dzielenie, zapis do st(0)
    fstp output
    break:

    mov %ebp, %esp
    pop %ebp
ret

# funkcja dodajaca liczby zmiennoprzecinkowe
.type asm_add, @function    
asm_add:       
    push %ebp
    mov %esp,%ebp

    finit
    fld input
    fld input2
    fadd %st(1), %st(0) # mnożenie, zapis do st(0)
    fstp output
    break:

    mov %ebp, %esp
    pop %ebp
ret