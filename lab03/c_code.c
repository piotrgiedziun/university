#include <stdio.h>

char *c_char = "This content came form c\n";
char *c_char_c = "Hello form c file (pointer)\n";
char *c_printf_s = "%s";

extern void c_function();

int main()
{
 printf("Hello form c file (default)\n");
 printf(c_printf_s, c_char_c);
 c_function();
 return 0;
}
