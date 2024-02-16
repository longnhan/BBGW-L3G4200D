#include "l3g4.h"

void i2cInit(void)
{
    int file;
    char filename[20];
    char buf[10];
    printf("i2c Init\n");
    // Open the I2C bus
    sprintf(filename, "%s", I2C_DEVICE);
    if ((file = open(filename, O_RDWR)) < 0) 
    {
        perror("Failed to open the bus.");
        return 1;
    }
    // Set the I2C slave address
    if (ioctl(file, I2C_SLAVE, DEVICE_I2C_ADR) < 0) 
    {
        perror("Failed to acquire bus access and/or talk to slave.");
        return 1;
    }
}
uint8_t getI2cData(uint8_t deviceAddress, uint8_t regAddress, uint8_t *buf)
{
    return 0;
}
uint8_t sendI2cData(uint8_t deviceAddress, uint8_t regAddress, uint8_t cmd)
{
    return 0;
}