N = 1000000;

x = [];
y = [];
for k = 0:(N-1)
	x(k+1) = floor(1000/bitand(k+1,(2^32)-1));
	y(k+1) = floor(1000/bitand(3*k*k+5*k+1,(2^32)-1));
end

media_x = 0;
for k = 1:N
	media_x = media_x + x(k)/N;
end

media_y = 0;
for k = 1:N
	media_y = media_y + y(k)/N;
end

dist_eucl = 0;
for k = 1:N
	dist_eucl = dist_eucl + (x(k)-y(k))^2;
end
dist_eucl = sqrt(dist_eucl);

disp("Resultado:")
disp(["   Media(x) = " num2str(media_x)]);
disp(["   Media(y) = " num2str(media_y)]);
disp(["   Dist_euclidiana(x,y) = " num2str(dist_eucl)]);