#include <stdio.h>

extern int add();
int a, b;

int main()
{
 printf("ASM addition (a+b=c)\n");
 printf("a = ");
 scanf("%d", &a);
 printf("b = ");
 scanf("%d", &b);

 printf("c = %d\n", add(a, b));
 return 0;
}
