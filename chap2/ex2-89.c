#include <stdio.h>
#include <limits.h>
#include <stdlib.h> 
/*  
 *  题目：计算2^x的浮点表示,x太小返回0，x太大返回+oo。
 *
 */

float u2f(unsigned a) {
    return *((float *)(&a));
}

float fpwr2(int x) {
    unsigned exp, frac;
    unsigned u;

    if (x < -149) {
        /* Too small. Return 0.0 */
        exp = 0;
        frac = 0;
    } else if (x < -126) {
        /* Denormalized result. */
        exp = 0;
        frac = 1 << (x + 149);
    } else if (x < 128) {
        /* Normalized result. */
        exp = x + 127;
        frac = 0;
    } else {
        /* Too big. Return +oo */
        exp = 0xff;
        frac = 0;
    }

    /* Pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    return u2f(u);
}

int main() {
    int i;
    for (i = -150; i < 150; ++i)
    {
        printf("2^%d=%e\n", i, fpwr2(i));
    }
}