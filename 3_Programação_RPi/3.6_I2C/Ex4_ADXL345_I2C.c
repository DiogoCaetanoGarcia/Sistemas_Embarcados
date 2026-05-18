#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_DEVICE "/dev/i2c-1"

// ADXL345 I2C Address
//#define ADXL345_ADDR 0x1D
#define ADXL345_ADDR 0x53

// Registers
#define DEVID_REG       0x00
#define BW_RATE_REG     0x2C
#define POWER_CTL_REG   0x2D
#define DATA_FORMAT_REG 0x31
#define DATAX0_REG      0x32

// Settings
#define ADXL345_RATE_200HZ 0x0B
#define ADXL345_RANGE_16G  0x03

int write_register(int file, uint8_t reg, uint8_t value)
{
	uint8_t buffer[2];

	buffer[0] = reg;
	buffer[1] = value;

	if (write(file, buffer, 2) != 2)
	{
		return -1;
	}

	return 0;
}

int read_register(int file, uint8_t reg)
{
	if (write(file, &reg, 1) != 1)
	{
		return -1;
	}

	uint8_t data;

	if (read(file, &data, 1) != 1)
	{
		return -1;
	}

	return data;
}

int read_multiple(int file, uint8_t reg, uint8_t *buffer, int length)
{
	if (write(file, &reg, 1) != 1)
	{
		return -1;
	}

	if (read(file, buffer, length) != length)
	{
		return -1;
	}

	return 0;
}

int main()
{
	int file;

	file = open(I2C_DEVICE, O_RDWR);

	if (file < 0)
	{
		perror("Failed to open I2C bus");
		return 1;
	}

	if (ioctl(file, I2C_SLAVE, ADXL345_ADDR) < 0)
	{
		perror("Failed to connect to sensor");
		return 1;
	}

	// Read device ID
	int deviceID = read_register(file, DEVID_REG);

	if (deviceID < 0)
	{
		printf("read device id: failed\n");
		return 1;
	}

	printf("0x%02X\n", deviceID);

	// Set data rate to 200 Hz
	if (write_register(file, BW_RATE_REG, ADXL345_RATE_200HZ) < 0)
	{
		printf("write rate: failed\n");
		return 1;
	}

	// Set range to ±16g + FULL_RES
	uint8_t format = ADXL345_RANGE_16G | 0x08;

	if (write_register(file, DATA_FORMAT_REG, format) < 0)
	{
		printf("write range: failed\n");
		return 1;
	}

	// Enable measurement mode
	if (write_register(file, POWER_CTL_REG, 0x08) < 0)
	{
		printf("start: failed\n");
		return 1;
	}

	while (1)
	{
		uint8_t data[6];

		if (read_multiple(file, DATAX0_REG, data, 6) < 0)
		{
			printf("update failed\n");
			break;
		}

		int16_t x = (int16_t)((data[1] << 8) | data[0]);
		int16_t y = (int16_t)((data[3] << 8) | data[2]);
		int16_t z = (int16_t)((data[5] << 8) | data[4]);

		printf("%d,%d,%d\n", x, y, z);

		usleep(300000); // 300 ms
	}

	close(file);

	return 0;
}
