#include <stdio.h>

extern void doit();
float input, output;

int main()
{ // program liczacy sqrt(a)
    printf("podaj a: ");
    scanf("%f", &input);
    doit(); // funkcja asm
    printf("a=%f\nsqrt(a)=%f\n", input, output);
    return 0;
}