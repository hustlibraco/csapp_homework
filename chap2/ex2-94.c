#include <stdio.h>
#include <limits.h>
#include <stdlib.h> 
/*  
 *  遵循位级浮点编码规则，实现具有如下原型的函数：

 *  // Compute 2*f.  If f is NaN, then return f.
 *  float_bits float_twice(float_bits f);

 *  对于浮点数 f，这个函数计算 2.0 *f。如果 f 是 NaN，你的函数应该简单返回 f。测
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

float_bits float_twice(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;
    if (exp == 0xff) {
        // return f if f = Inf or Nan
        return f;
    }
    if (exp == 0) {
        // denormalized number to normalized number
        if (frac >> 22) {
            exp = 1;
            frac &= 0x3fffff;
        }
        frac <<= 1;
    } else if (exp == 0xfe) {
        exp = 0xff;
        frac = 0;
    } else {
        exp++;
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
            is_equal = float_twice(i) == f2u(2 * f);
        } else {
            is_equal = float_twice(i) == i;
        }
        if (!is_equal) {
            printf("[%x]2.0*f = %e, float_twice = %e, %d\n", i, 2*f, u2f(float_twice(i)), is_equal);
            printf("[%x]2.0*f = %x, float_twice = %x, %d\n", i, f2u(2*f), float_twice(i), is_equal);
        }
        i++;
    } while (i);
    return 0;
}
 