SYSEXIT  = 1
SYSREAD = 3
SYSWRITE = 4
STDOUT = 1
STDIN = 0
EXIT_SUCCESS = 0
INT_SIZE = 4

.type sum, @function
	sum:
	pop %esi
	
	while:
		pop %edx
		pop %ebx
		adc %edx, %ebx
		
		#odkladaj wynik
		mov %esp, %edi # zapaniętaj adres stosu
		mov %eax, %esp # wpisz nowy adres stosu
		
		push %ebx
		add $INT_SIZE, %eax # przesuń wskaźnik wyników na następny
		
		#fix segmentation
		mov %edi, %esp
		
	loop while
  
  	push %esi
	ret

.global _start

_start:
    #eax - pointer na wyniki
    #ecx - ilość parametrów
    mov $3, %ebx
   
    #odkladam wynik
    mov %esp, %eax 
    mov %ebx, %ecx

    uzupelnij_zerami:
       push $0
    loop uzupelnij_zerami  
    
    #podaje wejscie
    push $2
    push $1
    push $8
    push $7
    push $2
    push $3  
    #ustaw wkaźnik wyniku na pierwszy element wyniku
    sub $INT_SIZE, %eax    
    #ustawienie ecx = ebx (ilosc iteracji)
    mov %ebx, %ecx    

    call sum

#sciaganie ze stosu
	mov %esp, %eax
	mov $3, %ecx
	mov $0, %ebx
	while_r:
		pop %ebx
	loop while_r

koniec:
    mov $SYSEXIT, %eax
    mov $EXIT_SUCCESS, %ebx
    int $0x80
