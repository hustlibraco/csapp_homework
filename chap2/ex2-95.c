#include <stdio.h>
#include <limits.h>
#include <stdlib.h> 
/*  
 *  遵循位级浮点编码规则，实现具有如下原型的函数：
 *
 *  // Compute (float) i
 *  float_bits float_i2f(int i);
 *
 *  对于浮点数 f，这个函数计算 (float)i 的位级表示。
 *  测试你的函数，对参数 f 可以取的所有 2^32 个值求值，将结果与你使用机器的浮点运
 *  算得到的结果相比较。
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

float_bits float_i2f(int i) {
    unsigned sign, frac, exp, frac_len = 0, overflow, tmp;
    if (i == 0) {
        return i;
    }
    sign = (unsigned)i >> 31;
    frac = sign ? -i : i;
    tmp = frac;
    while (tmp) {
        tmp >>= 1;
        ++frac_len;
    }
    frac &= (1 << --frac_len) - 1;
    exp = frac_len + 127;
    if (frac_len > 23) {
        // rounding
        overflow = frac & ((1 << (frac_len - 23)) - 1);
        frac = (frac >> (frac_len - 23));
        if (overflow > (1 << (frac_len - 24))) {
            ++frac;
        } else if (overflow == (1 << (frac_len - 24)) && frac & 1) {
            ++frac;
        }
        exp += (frac >= 0x800000);
        frac &= 0x7fffff;
    } else {
        frac <<= 23 - frac_len;
    }
    return (sign << 31) | (exp << 23) | frac;
}

int main(void)
{
    int i, is_equal;
    for (i = INT_MIN; i < INT_MAX; ++i)
    {
        is_equal = (float)i == u2f(float_i2f(i));
        if (!is_equal) {
            printf("[%d]i = %x, (float)i = %x, float_i2f(i) = %x, %d\n", i, i, f2u((float)i), float_i2f(i), is_equal);
        }
    }
    return 0;
}
 
