#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <unistd.h>

int main(void)
{
	struct pollfd pfd[2];
	char buffer;
	int btn_press;
	system("echo 4       > /sys/class/gpio/export");
	system("echo falling > /sys/class/gpio/gpio4/edge");
	system("echo in      > /sys/class/gpio/gpio4/direction");
	system("echo 17      > /sys/class/gpio/export");
	system("echo falling > /sys/class/gpio/gpio17/edge");
	system("echo in      > /sys/class/gpio/gpio17/direction");
	pfd[0].fd = open("/sys/class/gpio/gpio4/value", O_RDONLY);
	if(pfd[0].fd < 0)
	{
		puts("Erro abrindo /sys/class/gpio/gpio4/value");
		puts("Execute este programa como root.");
		return 1;
	}
	pfd[1].fd = open("/sys/class/gpio/gpio17/value", O_RDONLY);
	pfd[0].events = POLLPRI | POLLERR;
	pfd[1].events = POLLPRI | POLLERR;
	puts("Pressione o botao...");
	for(btn_press=0; btn_press<5; btn_press++)
	{
		pfd[0].revents = 0;
		pfd[1].revents = 0;
		lseek(pfd[0].fd, 0, SEEK_SET);
		read(pfd[0].fd, &buffer, 1);
		lseek(pfd[1].fd, 0, SEEK_SET);
		read(pfd[1].fd, &buffer, 1);
		poll(pfd, 2, -1);
		if((pfd[0].revents)&(POLLPRI|POLLERR))
			puts("Borda de descida em GPIO4!");
		if((pfd[1].revents)&(POLLPRI|POLLERR))
			puts("Borda de descida em GPIO17!");
	}
	close(pfd[0].fd);
	close(pfd[1].fd);
	system("echo 4  > /sys/class/gpio/unexport");
	system("echo 17 > /sys/class/gpio/unexport");
	return 0;
}
