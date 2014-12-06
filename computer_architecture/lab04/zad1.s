.align 32
.extern input
.extern output
.global doit

.section .text
.type doit, @function    

doit:       
push %ebp
mov %esp, %ebp

finit # inicjalizacja jednoski zmiennoprzecinkowej
      # przywraca flagą wartości domyślne
fld input # wczytanie liczby
fsqrt
fstp output # zapisanie wyniku

mov %ebp, %esp
pop %ebp
ret