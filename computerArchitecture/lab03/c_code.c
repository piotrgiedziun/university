#include <stdio.h>

char *c_char = "This content came form c\n\0";
char *c_char_c = "Hello form c file (pointer)\n\0";
char *c_printf_s = "%s";

extern void run();

int main() {
 //printf wartości podanej jako parametr
 printf("Hello form c file (default)\n\0");
 //printf zmiennej podanej jako parametr
 printf(c_printf_s, c_char_c);
 run(); //wywołanie kodu asm
 return 0;
}
