#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#define HMC5883L_ADDR 0x1E

int main() {

    int file;
    char *bus = "/dev/i2c-1";

    // Open I2C bus
    if ((file = open(bus, O_RDWR)) < 0) {
        perror("Failed to open the bus");
        return 1;
    }

    // Connect to HMC5883L
    if (ioctl(file, I2C_SLAVE, HMC5883L_ADDR) < 0) {
        perror("Failed to connect to the sensor");
        return 1;
    }

    printf("HMC5883L COMPASS SENSOR BEGIN\n");

    // Set continuous measurement mode
    uint8_t config[2];
    config[0] = 0x02;
    config[1] = 0x00;

    if (write(file, config, 2) != 2) {
        perror("Failed to initialize sensor");
        return 1;
    }

    while (1) {

        uint8_t reg = 0x03;

        // Select starting register
        if (write(file, &reg, 1) != 1) {
            perror("Failed to select register");
            break;
        }

        // Read 6 bytes
        uint8_t data[6];

        if (read(file, data, 6) != 6) {
            perror("Failed to read data");
            break;
        }

        // Combine bytes
        int16_t x = (data[0] << 8) | data[1];
        int16_t z = (data[2] << 8) | data[3];
        int16_t y = (data[4] << 8) | data[5];

        // Compute heading
        float heading = atan2((float)y, (float)x);

        if (heading < 0)
            heading += 2 * M_PI;

        float headingDegrees = heading * 180 / M_PI;

        // Print results
        printf("X Value: %d\n", x);
        printf("Y Value: %d\n", y);
        printf("Z Value: %d\n", z);
        printf("Heading: %.2f\n\n", headingDegrees);

        sleep(1);
    }

    close(file);

    return 0;
}