zeroFlag = 4 # ..00100
.align 32
.extern input
.extern input2
.extern output
.global doit

.section .text

.type doit, @function    
doit:       
    push %ebp
    mov %esp,%ebp

    finit
    fld input
    fld input2

    fxch  
    fdiv %st(1), %st(0)
    fstp output
    mov $0, %eax
    fstsw %ax
    
    and $zeroFlag, %ax # maska statusu błędu
    cmp $zeroFlag, %ax # sprawdzenie statusu błedu
    jne ZeroErrorNotFound
    call zerroerror # wywołanie funkcji obsługującej błąd
    # funkcja obsługi błędu może być zaimplementowana w asm
    # i nie wracać do dalszego wykonywania funkcji, lub
    # zaimplementowana w c (extern w asm)

    ZeroErrorNotFound:
    mov %ebp, %esp
    pop %ebp
ret