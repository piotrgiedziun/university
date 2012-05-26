.global Filter

.section .data
max: .long -1, -1, -1

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
#mov 22(%ebp) - parm
mov 24(%ebp), %ecx

mull %ebx
mull %ecx
movl %eax, %ecx

movq max, %mm1
while:
movq (%edi), %mm0
#pxor %mm1, %mm0
PAND %mm1, %mm0
movq %mm0, (%edi)
add $8, %edi
sub $7, %ecx

loop while

emms
mov %ebp, %esp
pop %ebp
ret