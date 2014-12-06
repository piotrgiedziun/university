SYSEXIT  = 1 
EXIT_SUCCESS = 0

.global _start

.type factR, @function
factR:
 cmpl $0 ,4(% esp )
 jne cont
 movl $1 ,%eax
 ret

.type cont, @function
cont :
 movl 4(%esp),%eax
 decl %eax
 pushl %eax 
 call factR
 addl $4,%esp
 imull 4(%esp),%eax 
 ret

_start:
  push $3
  call factR 

exit:
    mov $SYSEXIT, %eax
    mov $EXIT_SUCCESS, %ebx
    int $0x80
