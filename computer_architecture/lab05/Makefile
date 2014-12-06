showimage: filter.o showimage.o
	gcc -m32 -o showimage filter.o showimage.o -lSDL-1.2 -lSDL_image-1.2

showimage.o: showimage.c
	gcc -m32 -o showimage.o -c showimage.c

filter.o: filter.s
	gcc -m32 -o filter.o -c filter.s
