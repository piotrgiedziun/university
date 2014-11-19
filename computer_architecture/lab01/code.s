SYSEXIT = 1
SYSREAD = 3
SYSWRITE = 4
STDOUT = 1
STDIN = 0
EXIT_SUCCESS = 0

.section .data
.lcomm tab, 32

.section .text
msg_podaj: .ascii "Hi!\nEnter number:\n"
msg_podaj_len = . - msg_podaj
msg_podany: .ascii "Entered number:\n"
msg_podany_len = . - msg_podany

.global _start				#wskazanie punktu wejścia do programu

.type get_text, @function
get_text:
	mov $SYSWRITE, %eax
	mov $STDOUT, %ebx
	mov $msg_podaj, %ecx
	mov $msg_podaj_len, %edx
	int $0x80
	
	mov $SYSREAD, %eax 			#funkcja do wywołania - SYSREAD
	mov $STDIN, %ebx 			#1 arg. - syst. deskryptor stdin
	mov $tab, %ecx	 			#2 arg. - adres tablicy
	mov $32, %edx 				#3 arg. - długość łańcucha
	int $0x80					#wywołanie przerwania programowego
	ret

.type show_text, @function
show_text:
	mov $SYSWRITE, %eax 		#funkcja do wywołania - SYSWRITE
	mov $STDOUT, %ebx
	mov $msg_podany, %ecx
	mov $msg_podany_len, %edx
	int $0x80

	mov $SYSWRITE, %eax
	mov $STDOUT, %ebx
	mov $tab, %ecx
	mov $32, %edx
	int $0x80
	ret
	
.type exit, @function
exit:
	mov $SYSEXIT, %eax
	mov $EXIT_SUCCESS, %ebx
	int $0x80
	ret

_start:

call get_text				
call show_text
call exit
