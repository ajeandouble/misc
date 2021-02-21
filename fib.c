#include <stdio.h>
#include <stdlib.h>

int fib(int n) {
	static int memo[100] = {0};
	static char size = 0;

	if (n <= 2)	return 1;
	if (memo[n])	return memo[n];
	int result = fib(n - 2) + fib(n - 1);
	memo[n] = result;
	
	// dbg

	return result;
}

int main() {
	printf("%d\n", fib(1));
	printf("%d\n", fib(2));
	printf("%d\n", fib(3));
	printf("%d\n", fib(4));
	printf("%d\n", fib(5));
	printf("%d\n", fib(6));
	printf("%d\n", fib(7));
	printf("%d\n", fib(18));
}
