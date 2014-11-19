.global Filter

.section .data

.section .text

.type Filter, @function
Filter:

push %ebp
mov %esp, %ebp

# sciaganie ze stosu
mov 8(%ebp), %edi
mov 12(%ebp), %eax
mov 16(%ebp), %ebx
mov 18(%ebp), %esi
mov 24(%ebp), %ecx

mull %ebx
mull %ecx
movl %eax, %esi

add %edi, %esi
while:
movb (%edi), %ah
movb (%esi), %al

movb %al, (%edi)
movb %ah, (%esi)

inc %edi
dec %esi

cmp %edi, %esi
jne while

emms
mov %ebp, %esp
pop %ebp
ret