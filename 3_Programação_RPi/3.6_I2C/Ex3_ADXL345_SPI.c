#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define SPI_DEVICE "/dev/spidev0.0"

// Registers
#define DEVID_REG       0x00
#define BW_RATE_REG     0x2C
#define POWER_CTL_REG   0x2D
#define DATA_FORMAT_REG 0x31
#define DATAX0_REG      0x32

// Settings
#define ADXL345_RATE_200HZ 0x0B
#define ADXL345_RANGE_16G  0x03

static uint8_t mode = SPI_MODE_3;
static uint8_t bits = 8;
static uint32_t speed = 500000;

int spi_transfer(int fd, uint8_t *tx, uint8_t *rx, int length)
{
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = length,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	return ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
}

int write_register(int fd, uint8_t reg, uint8_t value)
{
	uint8_t tx[2];
	uint8_t rx[2];

	tx[0] = reg;
	tx[1] = value;

	if (spi_transfer(fd, tx, rx, 2) < 1)
	{
		return -1;
	}

	return 0;
}

int read_register(int fd, uint8_t reg)
{
	uint8_t tx[2];
	uint8_t rx[2];

	tx[0] = reg | 0x80; // Read bit
	tx[1] = 0x00;

	if (spi_transfer(fd, tx, rx, 2) < 1)
	{
		return -1;
	}

	return rx[1];
}

int read_multiple(int fd, uint8_t reg, uint8_t *buffer, int length)
{
	uint8_t tx[length + 1];
	uint8_t rx[length + 1];

	tx[0] = reg | 0xC0; // Read + Multi-byte
	for (int i = 1; i < length + 1; i++)
	{
		tx[i] = 0x00;
	}

	if (spi_transfer(fd, tx, rx, length + 1) < 1)
	{
		return -1;
	}

	for (int i = 0; i < length; i++)
	{
		buffer[i] = rx[i + 1];
	}

	return 0;
}

int main()
{
	int fd;

	fd = open(SPI_DEVICE, O_RDWR);

	if (fd < 0)
	{
		perror("Failed to open SPI device");
		return 1;
	}

	// Configure SPI
	ioctl(fd, SPI_IOC_WR_MODE, &mode);
	ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);

	// Read device ID
	int deviceID = read_register(fd, DEVID_REG);

	if (deviceID < 0)
	{
		printf("read device id: failed\n");
		return 1;
	}

	printf("0x%02X\n", deviceID);

	// Set data rate to 200 Hz
	if (write_register(fd, BW_RATE_REG, ADXL345_RATE_200HZ) < 0)
	{
		printf("write rate: failed\n");
		return 1;
	}

	// Set range to ±16g + FULL_RES
	uint8_t format = ADXL345_RANGE_16G | 0x08;

	if (write_register(fd, DATA_FORMAT_REG, format) < 0)
	{
		printf("write range: failed\n");
		return 1;
	}

	// Enable measurement mode
	if (write_register(fd, POWER_CTL_REG, 0x08) < 0)
	{
		printf("start: failed\n");
		return 1;
	}

	while (1)
	{
		uint8_t data[6];

		if (read_multiple(fd, DATAX0_REG, data, 6) < 0)
		{
			printf("update failed\n");
			break;
		}

		int16_t x = (int16_t)((data[1] << 8) | data[0]);
		int16_t y = (int16_t)((data[3] << 8) | data[2]);
		int16_t z = (int16_t)((data[5] << 8) | data[4]);

		printf("%d,%d,%d\n", x, y, z);

		usleep(300000);
	}

	close(fd);

	return 0;
}
