#include <stdio.h>

extern void run();

float addition(float a, int b) {
    printf("a=%f b=%d\n", a, b);
    return a+b;
}

int main() {
    run(); // start kodu asm
    return 0;
} 