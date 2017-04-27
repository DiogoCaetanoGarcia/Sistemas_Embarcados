#include <stdio.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <unistd.h>

int main(void)
{
	struct pollfd pfd;
	char buffer;
	int btn_press;
	system("echo 4       > /sys/class/gpio/export");
	system("echo falling > /sys/class/gpio/gpio4/edge");
	system("echo in      > /sys/class/gpio/gpio4/direction");
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
		read(pfd.fd, &buffer, 1);
		poll(&pfd, 1, -1);
		puts("Borda de descida!");
	}
	close(pfd.fd);
	system("echo 4 > /sys/class/gpio/unexport");
	return 0;
}
