N = 1000000;

function [a,b] = preencher_vetores(N)
	a = [];
	b = [];
	for k = 0:(N-1)
		a(k+1) = floor(1000/bitand(k+1, (2^32)-1));
		b(k+1) = floor(1000/bitand(3*k*k+5*k+1,(2^32)-1));
	end
endfunction

function media_a = calc_media(a)
	media_a = 0;
	N = length(a);
	for k = 1:N
		media_a = media_a + a(k)/N;
	end
endfunction

function dist_eucl = distancia_euclidiana(a, b)
	dist_eucl = 0;
	for k = 1:length(a)
		dist_eucl = dist_eucl + (a(k)-b(k))^2;
	end
	dist_eucl = sqrt(dist_eucl);
endfunction

if length(argv())>0
	profile on
end
[x,y] = preencher_vetores(N);
media_x = calc_media(x);
media_y = calc_media(y);
dist_eucl = distancia_euclidiana(x,y);
if length(argv())>0
	profile off
	profshow()
end

disp("Resultado:")
disp(["   Media(x) = " num2str(media_x)]);
disp(["   Media(y) = " num2str(media_y)]);
disp(["   Dist_euclidiana(x,y) = " num2str(dist_eucl)]);