#include <stdio.h>
#include <float.h>

extern void asm_div();
extern void asm_add();
float input, input2, output;

int main()
{
    //bład zero divide
    input = 2;
    input2 = 0;
    asm_div();
    printf("%f/%f=%f\n", input, input2, output);
    
    //bład overflow
    input = FLT_MAX;
    input2 = 1;
    asm_add();
    printf("%f+%f=%f\n", input, input2, output);
    return 0;
}
