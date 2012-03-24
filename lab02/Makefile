code: code.o
	ld -o code -melf_i386 code.o
	
code.o: code.s
	as -o code.o -g --32 code.s
