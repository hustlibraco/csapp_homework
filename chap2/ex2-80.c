#include <stdio.h>
#include <limits.h>
/*	
 *	题目要求不能使用w，但是可以使用m,n
 *	A.1(w-n)0(n) = ~0 << n
 *  B.0(w-n-m)1(n)0(m) = 1(n) << m = ~A << m
 *	显然A要满足n <= w，B要满足m+n <= w
 *
 */

int problemA(int n) {
	return ~0 << n;
}

int problemB(int m, int n) {
	return ~(~0 << n) << m;
}

int main() {
	printf("problemA(16)=0x%08x, problemB(3,12)=0x%08x\n", problemA(16), problemB(3,12));
    return 0;
}
