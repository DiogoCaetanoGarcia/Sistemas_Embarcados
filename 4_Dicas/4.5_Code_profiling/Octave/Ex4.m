N = 1000000;

function [a,b] = preencher_vetores(N)
	k = 0:(N-1);
	a = floor(1000./bitand(k+1, (2^32)-1));
	b = floor(1000./bitand(3*(k.*k)+5*k+1,(2^32)-1));
endfunction

function media_a = calc_media(a)
	media_a = mean(a);
endfunction

function dist_eucl = distancia_euclidiana(a, b)
	dist_eucl = sqrt(sum((a-b).^2));
endfunction

if length(argv())>1
	profile on
end
[x,y] = preencher_vetores(N);
media_x = calc_media(x);
media_y = calc_media(y);
dist_eucl = distancia_euclidiana(x,y);
if length(argv())>1
	profile off
	profshow()
end

disp("Resultado:")
disp(["   Media(x) = " num2str(media_x)]);
disp(["   Media(y) = " num2str(media_y)]);
disp(["   Dist_euclidiana(x,y) = " num2str(dist_eucl)]);