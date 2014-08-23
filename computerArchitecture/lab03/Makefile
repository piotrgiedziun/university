code: code.o c_code.o
	gcc -m32 -o code code.o c_code.o
	
c_code.o: c_code.c
	gcc -m32 -o c_code.o -c c_code.c

code.o: code.s
	gcc -m32 -o code.o -c code.s
