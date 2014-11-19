#include <stdio.h>

extern int add();
extern void upper();
int a;
int b;
char s[32];

int main()
{
    // pobranie a, b
    // wywołanie funkcji add z asm
    // parametry typu int
    // zwraca int
    printf("a+b=c\n");
    printf("a = ");
    scanf("%d", &a);
    printf("b = ");
    scanf("%d", &b);
    printf("c = %d\n", add(a, b));
    
    // funkcja zamieniająca pierwszy znak na wielki
    // paramtetr typu char*
    printf("podaj ciag znakow\n");
    scanf("%s", &s);
    upper(s);
    
    return 0;
}
