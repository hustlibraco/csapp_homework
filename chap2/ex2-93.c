#include <stdio.h>
#include <limits.h>
#include <stdlib.h> 
/*  
 *  遵循位级浮点编码规则，实现具有如下原型的函数：

 *  // Compute 0.5*f.  If f is NaN, then return f. 
 *  float_bits float_half(float_bits f);

 *  对于浮点数 f，这个函数计算 0.5*f。如果 f 是 NaN，你的函数应该简单返回 f。测
 *  试你的函数，对参数 f 可以取的所有 2^32 个值求值，将结果与你使用机器的浮点运
 *  算得到的结果相比较。
 * 
*/

typedef unsigned float_bits;

float u2f(unsigned a) {
    return *((float *)(&a));
}

unsigned f2u(float a) {
    return *((unsigned *)(&a));
}

int is_number(float x) {
    return (x == x);
}

float_bits float_half(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;
    if (exp == 0xff) {
        // return f if f = Inf or Nan
        return f;
    }
    if (exp == 1) {
        // normalized number to denormalized number
        // except for frac = 0x7fffff
        exp = 0;
        frac |= 0x800000;
    }
    if (exp == 0) {
        frac = (frac >> 1) + ((frac & 3) == 3);
    } else {
        exp -= 1;
    }
    return (sign << 31) | (exp << 23) | frac;
}

int main(void)
{
    unsigned i = 0;
    int is_equal;
    float f;
    do {
        f = u2f(i);
        if (is_number(f)) {
            is_equal = float_half(i) == f2u(0.5 * f);
        } else {
            is_equal = float_half(i) == i;
        }
        if (!is_equal) {
            printf("[%x]0.5*f = %e, float_half = %e, %d\n", i, 0.5*f, u2f(float_half(i)), is_equal);
        }
        i++;
    } while (i);
    return 0;
}
 