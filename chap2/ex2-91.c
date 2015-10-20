#include <stdio.h>
#include <limits.h>
#include <stdlib.h> 
/*  
 *  遵循位级浮点编码规则，实现具有如下原型的函数：

 *  // Compute |f|.  If f is Nan, then return f. 
 *  float_bits float_absval(float_bits f);

 *  对于浮点数 f，这个函数计算 |f|。如果 f 是 NaN，你的函数应该简单地返回 f。测试
 *  你的函数，对参数 f 可以取的所有 2^32 个值求值，将结果与你使用机器的浮点运算
 *  得到的结果相比较。
 * 
*/

typedef unsigned float_bits;

float u2f(unsigned a) {
    return *((float *)(&a));
}

unsigned f2u(float a) {
    return *((unsigned *)(&a));
}

float_bits float_absval(float_bits f) {
    unsigned sign = f >> 31; 
    return sign == 1 ? (f & 0x7fffffff) : f;
}

int main(void)
{
        float f = -0.0;
        unsigned uf = f2u(f);
        printf("%f(0x%X): %f\n", f, uf, u2f(float_absval(uf)));

        f = 0.0;
        uf = f2u(f);
        printf("%f(0x%X): %f\n", f, uf, u2f(float_absval(uf)));

        f = 1.0;
        uf = f2u(f);
        printf("%f(0x%X): %f\n", f, uf, u2f(float_absval(uf)));

        f = -1.0;
        uf = f2u(f);
        printf("%f(0x%X): %f\n", f, uf, u2f(float_absval(uf)));

        f = u2f(0x7F800000);    /* +oo */
        uf = f2u(f);
        printf("%f(0x%X): %f\n", f, uf, u2f(float_absval(uf)));

        f = u2f(0xFF800000);    /* -oo */
        uf = f2u(f);
        printf("%f(0x%X): %f\n", f, uf, u2f(float_absval(uf)));

        f = u2f(0x7F800001);    /* NaN */
        uf = f2u(f);
        printf("%f(0x%X): %f\n", f, uf, u2f(float_absval(uf)));

        return 0;
}