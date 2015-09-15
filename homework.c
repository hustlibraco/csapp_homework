#include <stdio.h>
#include <string.h>

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

int main()
{	
	int i;
	for (i = -32; i < 32; ++i)
	{
		printf("fits_bit(%d, 4) is %d\n", i, fits_bit(i, 4));
	}
	return 0;
}
