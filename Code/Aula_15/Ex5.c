#include <stdio.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <unistd.h>

#define N 100
int main(void)
{
	struct pollfd pfd;
	char buffer;
	int btn_press;
	char vals[N]={0}, pos=0, i, s;
	system("echo 4      > /sys/class/gpio/export");
	system("echo rising > /sys/class/gpio/gpio4/edge");
	system("echo in     > /sys/class/gpio/gpio4/direction");
	pfd.fd = open("/sys/class/gpio/gpio4/value", O_RDONLY);
	if(pfd.fd < 0)
	{
		puts("Erro abrindo /sys/class/gpio/gpio4/value");
		puts("Execute este programa como root.");
		return 1;
	}
	pfd.events = POLLPRI | POLLERR;
	pfd.revents = 0;
	puts("Pressione o botao...");
	for(btn_press=0; btn_press<5; btn_press++)
	{
		lseek(pfd.fd, 0, SEEK_SET);
		read(pfd.fd, &buffer, 1);
		poll(&pfd, 1, -1);
		puts("Borda de descida!");
		//usleep(200000);
		pos=s=0;
		while(s<(N/2+1))
		{
			lseek(pfd.fd, 0, SEEK_SET);
			read(pfd.fd, &buffer, 1);
			vals[pos] = buffer-'0';
			pos=(pos+1)%N;
			for(s=i=0;i<N;i++) s+=vals[i];
		}
	}
	close(pfd.fd);
	system("echo 4 > /sys/class/gpio/unexport");
	return 0;
}
