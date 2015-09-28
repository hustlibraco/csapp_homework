#include <stdio.h>
#include <limits.h>
#include <stdlib.h> 
/*  
 *  1.32位机器
 *  2.补码表示
 *  3.算术右移
 *
 */

int main() {
    int x = random();
    int y = random();
    unsigned ux = (unsigned) x;
    unsigned uy = (unsigned) y;

    // Fasle: y=INT_MIN
    int A = (x>INT_MIN) == (-x<-INT_MIN);
    printf("A=%d\n", A);

    // True: 补码乘法和左移等价
    int B = ((x+y)<<5) + x-y == 31*y+33*x;
    printf("B=%d\n", B);

    // False: ~x+~y=(-x-1)+(-y-1)=-(x+y)-1-1=~(x+y)-1
    int C = ~x+~y == ~(x+y);
    printf("C=%d\n", C);

    // True: 对于无符号数和有符号数，补码运算是相同的
    int D = (int)(ux-uy) == -(y-x);
    printf("D=%d\n", D);

    // True: 这个操作会损失x的最低有效位，无论对于符号数和非符号数，最低位都是代表正值
    int E = ((x>>1)<<1) <= x;
    printf("E=%d\n", E);
}