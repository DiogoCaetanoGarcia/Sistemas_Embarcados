#include <stdio.h>

long long fib(long long n)
{
	if(n<=1)
		return n;
	return fib(n-1)+ fib(n-2);
}

int main(void)
{
	long long n = 25, result = fib(n);
	printf("Fibonacci(%lld) = %lld\n", n, result);
	return 0;
}
