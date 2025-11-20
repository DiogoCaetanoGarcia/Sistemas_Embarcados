n = 25;

function f = fib(n)
	if n <=1
		f = n;
	else
		f = fib(n-1)+fib(n-2);
	end
endfunction

profile on
result = fib(n);
disp(["Fibonacci(" num2str(n)  ") = " num2str(result)]);
profile off
profshow()
