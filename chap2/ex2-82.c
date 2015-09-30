#include <stdio.h>
#include <limits.h>
#include <stdlib.h> 
/*  
 *  一些数字的二进制表示是由形如0.yyyyyyy···的无穷串组成的，其中一个y是一个k位的序列。
 *  例如,1/3的二进制表示是0.010101···(y=01),1/5的二进制表示是0.001100110011···(y=0011)。
 *
 *  A. 设Y=B2Uk(y),也就是说，这个数具有二进制表示y。给出一个Y和k组成的公式表示这个无穷串的值。
 *  提示：请考虑将二进制小数点右移k位的结果。
 *  
 *  设无穷串值为x。x*2^k = Y + x, 所以 x = Y/(2^k-1)
 *
 *  B. 对于下列y的值，串的数值是多少？
 *  (a) 001     1/7
 *  (b) 1001    3/5
 *  (c) 000111  7/63
 *
 */
float func_A(int Y, int k) {
    return (float)Y / ((1<<k) - 1);
}

int main() {
    // 001
    int Y = 1, k = 3;
    printf("func_A(%d,%d)=%f\n", Y, k, func_A(Y,k));
    // 1001
    Y = 9, k = 4;
    printf("func_A(%d,%d)=%f\n", Y, k, func_A(Y,k));
    // 000111
    Y = 7, k = 6;
    printf("func_A(%d,%d)=%f\n", Y, k, func_A(Y,k));
    return 0;
}