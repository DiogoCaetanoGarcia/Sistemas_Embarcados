#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <unistd.h>

int main(void)
{
	struct pollfd pfd;
	char buffer;
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
	// De acordo com a documentacao da interface Sysfs para GPIO
	// (https://www.kernel.org/doc/Documentation/gpio/sysfs.txt),
	// eh necessario ler o arquivo "value" antes de fazer o poll() nele
	read(pfd.fd, &buffer, 1);
	// Tambem de acordo com a documentacao da interface Sysfs para GPIO
	// (https://www.kernel.org/doc/Documentation/gpio/sysfs.txt),
	// o poll() deve ser feito considerando os sinais POLLPRI e POLLERR
	pfd.events = POLLPRI | POLLERR;
	pfd.revents = 0;
	puts("Pressione o botao...");
	poll(&pfd, 1, -1);
	puts("Borda de descida!");
	close(pfd.fd);
	system("echo 4 > /sys/class/gpio/unexport");
	return 0;
}
