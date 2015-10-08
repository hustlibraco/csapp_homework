#include <stdio.h>
#include <limits.h>
#include <stdlib.h> 
/*  
 *  原题：float_ge测试比较浮点数大小，f2u返回浮点数的补码表示（不改变位级）。
 *  思路：两个正浮点数被解释成无符号数时，大小关系不改变。IEEE有意如此设计使得浮点数能够按照整数排序函数排序。
 *        如果浮点数是负数，符号位为1，此时对应更大的无符号数虽然有更大的绝对值，但是由于是负数，所以排序要反过来。
 *  答案：根据题目条件正负零值相等，那么就有以下四种情况。
 *          1. sx=0, sy=1
 *          2. sx=sy=0, ux>=uy
 *          3. sx=sy=1, ux<=uy
 *          4. ux=INT_MIN, uy=0
 *        根据无符号数运算规则, sx=sy=0且ux>=uy <=> (ux-uy) & INT_MIN == 0, sx=sy=1且ux<=uy <=> (ux-uy) & INT_MIN == INT_MIN
 */

unsigned f2u(float a) {
    return *((unsigned *)(&a));
}

int float_ge(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);
    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;
    return (!sx & !sy) && !((ux - uy) & INT_MIN) || (sx & sy) && ((ux - uy) & INT_MIN) || ux==INT_MIN && !uy || (!sx & sy);
}

int main() {
    float x = 1.2, y = 1.1;
    int ret = float_ge(x, y);
    printf("float_ge(%f,%f) = %d\n", x, y, ret);
    x = 1.2, y = -1.1, ret = float_ge(x, y);
    printf("float_ge(%f,%f) = %d\n", x, y, ret);
    x = -1.2, y = 1.1, ret = float_ge(x, y);
    printf("float_ge(%f,%f) = %d\n", x, y, ret);
    x = -1.2, y = -1.1, ret = float_ge(x, y);
    printf("float_ge(%f,%f) = %d\n", x, y, ret);
    x = -1.1, y = -1.2, ret = float_ge(x, y);
    printf("float_ge(%f,%f) = %d\n", x, y, ret);
    x = +0.0, y = -0.0, ret = float_ge(x, y);
    printf("float_ge(%f,%f) = %d\n", x, y, ret);
    x = -0.0, y = +0.0, ret = float_ge(x, y);
    printf("float_ge(%f,%f) = %d\n", x, y, ret);
    return 0;
}