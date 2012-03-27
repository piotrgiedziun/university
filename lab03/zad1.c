#include <stdio.h>

extern void c_function();

int main()
{
 printf("Hello form c file\n");
 c_function();
 return 0;
}
