import cProfile

def fib(n):
	if n <=1:
		return n
	return fib(n-1) + fib(n-2)

def main():
	n = 25
	result = fib(n)
	print(f"Fibonacci({n}) = {result}")

cProfile.run('main()')
#main()
