.global Filter .section .data
maska: .long -1, -1, -1 .section .text
.type Filter, @function Filter:
push %ebp
mov %esp, %ebp
# sciaganie ze stosu
mov 8(%ebp), %edi mov 12(%ebp), %eax mov 16(%ebp), %ebx mov 18(%ebp), %esi mov 24(%ebp), %ecx
# wyliczanie rozmiaru obrazu
mull %ebx
mull %ecx
movl %eax, %ecx
# rozmiar jest w %ecx
# 11111.. do %mm1
movq maska, %mm1
while:
# odczytywanie kolejnych części obrazka (64 bity)
movq (%edi), %mm0
# xor z 1111.. -> wartość odwrotna
pxor %mm1, %mm0
# zapis do outputu
movq %mm0, (%edi)
# przesunięcie wskaźnika
add $8, %edi
# sub 8 (-7 i -1 w loop) od ecx sub $7, %ecx
loop while
emms
mov %ebp, %esp pop %ebp
ret