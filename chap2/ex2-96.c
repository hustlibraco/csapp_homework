#include <stdio.h>
#include <limits.h>
#include <stdlib.h> 
/*  
 *  遵循位级浮点编码规则，实现具有如下原型的函数：
 *
 *	// Compute (int) f.
 *  // If conversion causes overflow or f is NaN, return 0x80000000
 *  int float_f2i(float_bits f);
 *
 *  对于浮点数 f，这个函数计算 (int)f。你的函数应该向零舍入。如果f 不能用整数表示
 *  （例如，超出表示范围，或者它是一个 NaN），那么函数应该返回0x80000000。测试你
 *  的函数，对参数 f 可以取的所有 2^32 个值求值，将结果与你使用机器的浮点运算得到
 *  的结果相比较。
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


int float_f2i(float_bits f) {
    unsigned sign = f>>31;
    int exp = (f>>23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    int e = exp - 127;                                                                                      
    if (exp == 0xff)
    {
        // NaN or Inf
        return 0x80000000;
    } else if (exp == 0) {
        // f < 0
        return 0;
    // These two conditions above can be merged into the others. Show this for understanding.
    } else if (e < 0) {
        // e < 0, 1<= M <2
        return 0;
    } else if (e > 30) {
        // to big for int
        return 0x80000000;
    } else {
        int i = (1 << 23) + frac;
        if (e > 23) {
            i <<= (e - 23);
        } else {
            i >>= (23 - e);
        }
        return !sign ? i : -i;
    }
}

int main(void)
{
    unsigned u, is_equal;
    float f;
    for (u = 0; u != 0xffffffff; ++u)
    {
        f = u2f(u);
        is_equal = (int)f == float_f2i(u);
        if (!is_equal) {
            printf("[0x%x]f = %e, (int)f = %x, float_f2i(u) = %x\n", u, f, (int)f, float_f2i(u));
        }
    }
    return 0;
}
 
