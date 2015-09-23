#include <stdio.h>
#include <string.h>
#include <limits.h>
// 2.63
int sra(int x, int k) {
	/* Perform shift logically */
	int xsrl = (unsigned) x >> k;
	int flag = !(x & ~0 << (sizeof(int) << 3) - 1) - 1;  /* pos or =0:0x0, neg:0xffffffff */
	return xsrl | flag << (sizeof(int) << 3) - k;
	// if (x >= 0)
	// 	return xsrl;
	// else
	// 	return xsrl | ~0 << (sizeof(int) << 3) - k
}

unsigned srl(unsigned x, int k) {
	/* Perform shift arithmetically */
	unsigned xsra = (int) x >> k;
	return xsra & ~(~0 << (sizeof(int) << 3) - k);	// 不论x是何值，移位产生的bit必须为0
}

int checkpos(int x) {
	return !(x & ~0 << (sizeof(int) << 3)- 1);
}

// 2.64
int any_even_one(unsigned x) {
	return !!(x & 0xaaaaaaaa);
}

// 2.65
// 原理是x(左半部分) ^ x(右半部分) 和 x本身的奇偶性相同，
// 所以不断二分到最后一位即可判断
// 至于原理的证明需要去研究一下
int even_ones(unsigned x)
{
	x ^= (x >> 16);
	x ^= (x >> 8);
	x ^= (x >> 4);
	x ^= (x >> 2);
	x ^= (x >> 1);
	return !(x & 1);    
}

// 2.66
// 先将 x 转换成形如 [0...011...1] 的位向量
// x - (x >> 1) 就可以得到最左边的1了
int leftmost_one(unsigned x) {
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16; // 最后一步移动 w/2=16 位
	return x - (x >> 1);
}

// 2.67
// int bad_int_size_is_32() {
// 	int set_msb = 1 << 31;
// 	int beyond_msb = 1 << 32;	// 在有些机器上，移位不能超过字长，移位数会自动对字长求模，32mod32=0
// 	printf("beyond_msb is 0x%08x\n", beyond_msb);
// 	return set_msb && !beyond_msb;
// }

int int_size_is_32_b() {
	int set_msb = 1 << 31;
	int beyond_msb = set_msb << 1;
	return set_msb && !beyond_msb;
}

int int_size_is_32_c() {
	int set_msb = 1 << 15 << 15 << 1;
	int beyond_msb = set_msb << 1;
	return set_msb && !beyond_msb;
}

// 2.68
int lower_bits(int x, int n) {
    return x & (~0U >> ((sizeof(int) << 3) - n));
}

// 2.69
unsigned rotate_right(unsigned x, int n) {
	return x >> n | x << (sizeof(unsigned) << 3) - n;
	// 避免移位超过字长的写法
	// return x >> n | x << (sizeof(int) << 3) - n - 1 << 1
}

// 2.70
int fits_bit(int x, int n) {
	// x >> n == 0 or x >> n == -1
	return !(x >> n) | !~(x >> n);
}

// 2.71
typedef unsigned packed_t;
// 应该是没有进行符号扩展
int xbyte(packed_t word, int bytenum) {
	return word >> (bytenum << 3) & 0xFF;
}

int xbyte_b(packed_t word, int bytenum) {
	return (int)word << ((3 - bytenum) << 3) >> 24; 
}

// 2.72
// a.因为size_t是无符号类型，与maxbytes运算的结果转算成无符号数，始终大于等于0
// b.if (maxbytes >= sizeof(val))

// 2.73
int saturating_add(int x, int y) {
	int sum = x + y;
	int w = (sizeof(int) << 3) - 1;
	int sbx = x >> w;
	int sby = y >> w;
	int sbsum = sum >> w;
	int pos_ovf = ~sbx & ~sby & sbsum;  // 0xffffffff when positive overflow, else 0
	int neg_ovf = sbx & sby & ~sbsum;	// 0xffffffff when negtive overflow, else 0
	int no_ovf = ~(pos_ovf|neg_ovf);	// 0xffffffff when add normally, 0 when overflow
	return (pos_ovf & INT_MAX) | (neg_ovf & INT_MIN) | (no_ovf & sum);
}

// 2.74
int tsub_ovf(int x, int y) {
	int sub = x - y;
	int w = (sizeof(int) << 3) - 1;
	int sbx = x >> w;
	int sby = y >> w;
	int sbsub = sub >> w;
	int pos_ovf = !sbx && sby && sbsub;  // x >= 0 and y < 0 and sub < 0
	int neg_ovf = sbx && !sby && !sbsub; // x < 0 and y >= 0 and sub >= 0
	return (pos_ovf | neg_ovf);
	// 当xy异号，ysub同号的时候产生溢出，所以可以简写为
	// return (sbx != sby) && (sby == sbsub);
}

// 2.75
// 根据书上2-18公式：x'*y' = x*y + (msb(x)*y + msb(y)*x)*2^w + msb(x)*msb(y)*(2^2w)
// unsigned_high_prod(x, y) = (x'*y') / (2^w) = signed_high_prod(x,y) + (msb(x)*y + msb(y)*x) + msb(x)*msb(y)*(2^w) (超出了unsigned表示范围)
//                          = signed_high_prod(x,y) + (msb(x)*y + msb(y)*x)
// 其中msb表示最高有效位，2^w表示2的w次方
// int乘法的高w位
int signed_high_prod(int x, int y) {
	return 0;
} 
unsigned unsigned_high_prod(unsigned x, unsigned y) {
	unsigned w = sizeof(int) << 3;
	int msb_x = (int)x >> w-1;
	int msb_y = (int)y >> w-1;
	return signed_high_prod(x, y) + (msb_x & y) + (x & msb_y);  
}

// 2.76
int shift_multiply(int c, int k) {
	if (k == 5) {
		return (c << 2) + c;
	} else if (k == 9) {
		return (c << 3) + c;
	} else if ( k == 30) {
		return (c << 5) - (c << 1);
	} else if (k == -56) {
		return (c << 3) - (c << 6);
	} else {
		return c;
	}
}

// 2.77
int divide_power2(int x, int k) {
	int w = sizeof(int) << 3;
	x += (x >> w - 1) & ((1 << k) - 1);   // ceil(x/y) = floor((x+y-1)/y)
	return x >> k;
}

// 2.78
int mul5div8(int x) {
	int w = sizeof(int) << 3;
	x = (x << 2) + x;
	x += (x >> w - 1) & 7;
	return x >> 3;
}

// 2.79
/*
 * 对于计算 5/8x 的值，可以理解为两种情况：
 *
 *     1. 5/(8*x)
 *     2. (5/8)*x
 *
 * 对于第一种情况，x != 0 时，所得的结果是 0。x == 0 时，结果是没有定义的。对于这
 * 种求值，没有意义。因此，下面我们将题目理解为求值 (5/8)*x。
 *
 * 基本的思路是，5*x/8 = x/2 + x/8 + f
 *
 * f 的取值是 x/2 和 x/8 的小数部分之和 >=1 时，f=1。对于负数的情况，小数点之和
 * <= -1，则 f = -1。否则，f=0。
 *
 * 对于正数的情况，求两个整数的小数点之和就是截断两个数的最低三位，然后右移 3 位。
 *
 * 考虑负数的情况，我们可以发现，最低三位的数值+(-8)就是余数的数值（此时余数小于
 * 0）。对两个整数都这样处理，我们就可以得到两个负数的余数之和。然后加上偏执值右
 * 移 3 位，得到的就是小数点之和。只有当符号位和最低三位数值都是 1 时，才会有
 * f=-1。
 */
int fiveeights(int x) {
	int w = sizeof(int) << 3;
	int sign = (x & INT_MIN) >> w - 1;
	int pos_base = (x >> 1) + (x >> 3);
	int neg_base = (x + 1 >> 1) + (x + 7 >> 3);
	int pos_bias = (((x & 1) << 2) + (x & 7)) >> 3;
	int neg_bias = ((-(x & 1) & 1) << 2) + (-(x & 7) & 7) >> 3;
	return (sign & neg_base - neg_bias) | (~sign & pos_base + pos_bias);

}

int main()
{
	int i;
	for (i = -27; i < 27; ++i)
	{
		printf("[1] fiveeights(%d) = %d\n", i, fiveeights(i));
		printf("[2] %d * 5 / 8 = %d\n", i, 5 * i / 8);
		printf("[3] %d >> 1 + %d >> 3 = %d\n", i, i, (i >> 1) + (i >> 3));
	}
	return 0;
}
