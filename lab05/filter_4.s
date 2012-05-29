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
movl %eax, %ecx

while:
movq (%edi), %mm0
movq %mm0, -4(%edi)
add $8, %edi
sub $7, %ecx
loop while

emms
mov %ebp, %esp
pop %ebp
ret