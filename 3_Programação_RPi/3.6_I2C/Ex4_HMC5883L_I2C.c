#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

typedef struct
{
	int i2c_fd;
	unsigned char ender_QMC;	// endereço I2C do QMC5883
	unsigned char regCR1_QMC;	// registrador de configuração
	unsigned char regSR_QMC;	// registador set/reset
	unsigned char regXL_QMC;	// primeiro registrador de dados
	unsigned char regST_QMC;	// registrador de status
	float declination;
	float xMin, xMax, escX, offX;
	float yMin, yMax, escY, offY;
} QMC_data;

QMC_data qmc;

void ctrl_c(int sig);
void config_QMC(QMC_data *q, unsigned char adress);
float setDeclination(QMC_data *q, float graus , float mins, char dir);
// Le a direção da bússola em graus (0 a 360) em relação à marcação do eixo X
// Assume que a bússola esta na horizontal
int leDirecao(QMC_data *q);
void pedeDados(QMC_data *q, unsigned char regStatus, unsigned char regDados);
// Inicia processo de calibração
void iniciaCal(QMC_data *q);
// Encerra a calibração
void encerraCal(QMC_data *q);
void calibra(QMC_data *q);

// Código fez uma única leitura fixa várias vezes
int main(void)
{
	signal(SIGINT, ctrl_c);
	puts("Pressione CTRL+C para encerrar o programa.");
	config_QMC(&qmc, 0x1e);
	calibra(&qmc);
	while(1)
	{
		sleep(1);
		printf("Angulo = %do\n", leDirecao(&qmc));
	}
	return 0;
}

void ctrl_c(int sig)
{
	close(qmc.i2c_fd);
	exit(-1);
}

void config_QMC(QMC_data *q, unsigned char adress)
{
	q->ender_QMC = adress; // endereço I2C do QMC5883
	q->regCR1_QMC = 9;	 // registrador de configuração
	q->regSR_QMC = 11;	 // registador set/reset
	q->regXL_QMC = 0;		// primeiro registrador de dados
	q->regST_QMC = 6;		// registrador de status
	q->escX = 1.0;
	q->escY = 1.0;
	q->offX = 0.0;
	q->offY = 0.0;
	unsigned char dados[2];

	q->i2c_fd = open("/dev/i2c-1", O_RDWR);
	ioctl(q->i2c_fd, I2C_SLAVE, q->ender_QMC);
	dados[0] = q->regSR_QMC;
	dados[1] = 0x01;
	write(q->i2c_fd, dados, 2);
	dados[0] = q->regCR1_QMC;
	dados[1] = 0x0D;
	write(q->i2c_fd, dados, 2);
}

float setDeclination(QMC_data *q, float graus , float mins, char dir)
{
	float declination = (graus + mins / 60.0) * M_PI / 180.0;
	if (dir == 'W')
	{
		declination = -declination;
	}
	return declination;
}
 
// Le a direção da bússola em graus (0 a 360) em relação à marcação do eixo X
// Assume que a bússola esta na horizontal
int leDirecao(QMC_data *q)
{
	char d[6];
	float x, y, z;
 
	// Le a intesidade do campo magnético
	pedeDados(q, q->regST_QMC, q->regXL_QMC);
	read(q->i2c_fd, d, 6);
	x = (float)(d[0] + (d[1]<<8));
	y = (float)(d[2] + (d[3]<<8));
	z = (float)(d[4] + (d[5]<<8));
 
	// Registra mínimo e máximo para a calibração
	q->xMin = (x < q->xMin) ? x : q->xMin;
	q->xMax = (x > q->xMax) ? x : q->xMax;
	q->yMin = (y < q->yMin) ? y : q->yMin;
	q->yMax = (y > q->yMax) ? y : q->yMax;
	
	// corrige e calcula o angulo em radianos
	float xC = (x - q->offX) * q->escX;
	float yC = (y - q->offY) * q->escY;
	float angulo = atan2(yC, xC) + q->declination;
 
	// Garante que está entre 0 e 2*PI
	if (angulo < 0)
		angulo += 2.0 * M_PI;
	else if (angulo >= 2 * M_PI)
		angulo -= 2.0 * M_PI;
	 
	// Converte para graus
	return round((angulo * 180.0) / M_PI);
}
 
void pedeDados(QMC_data *q, unsigned char regStatus, unsigned char regDados)
{
	unsigned char d[6];
	// Espera ter um dado a ler
	do
	{
		write(q->i2c_fd, &regStatus, 1);
		read(q->i2c_fd, d, 2);
	} while ((d[1] & 1) == 0);
	write(q->i2c_fd, &regDados, 1);
	read(q->i2c_fd, &d, 6);
}
 
// Inicia processo de calibração
void iniciaCal(QMC_data *q)
{
	q->xMax = q->yMax = -32768.0;
	q->xMin = q->yMin =  32767.0;
}
 
// Encerra a calibração
void encerraCal(QMC_data *q)
{
	// Offset para centralizar leituras em zero
	q->offX = (q->xMax + q->xMin) / 2.0;
	q->offY = (q->yMax + q->yMin) / 2.0;
 
	// Escala para ter a mesma variação nos dois eixos
	float varX = q->xMax - q->xMin;
	float varY = q->yMax - q->yMin;
	if (varY > varX)
	{
		q->escY = 1.0;
		q->escX = varY / varX;
	} else
	{
		q->escX = 1.0;
		q->escY = varX / varY;
	}
}

long millis(void)
{
	return ((long)clock())*1000/CLOCKS_PER_SEC;
}

void delay(long t)
{
	long t0 = millis();
	while((millis()-t0)<t);
}

void calibra(QMC_data *q)
{
	int pos=0;
	iniciaCal(q);
	long tmpFim = millis() + 20000L;
	printf("t0 = %ld\n", tmpFim - 20000L);
	while (millis() < tmpFim)
	{
		leDirecao(q);
		//aponta(pos);
		pos += 5;
		if (pos == 360)
		{
			pos = 0;
		}
		delay (10);
	}
	encerraCal(q);
}
