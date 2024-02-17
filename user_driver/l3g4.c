#include "l3g4.h"

void i2cInit(void)
{
    int file;
    char filename[20];
    uint8_t buf[1]={0};
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
    //init sensor read device name
    getI2cData(file, DEVICE_NAME, buf, 1);
    printf("devce name: 0x%x\n", buf[0]);
}
void i2cClose(uint8_t file)
{
    close(file);
}
uint8_t getI2cData(int file, uint8_t regAddress, uint8_t *buf, uint8_t size)
{
    uint8_t ret = 0;
    write(file, &regAddress, 1);
    read(file, buf, size);
    return ret;
}
uint8_t sendI2cData(int file, uint8_t regAddress, uint8_t cmd)
{
    uint8_t ret = 0;
    write(file, &regAddress, 1);
    write(file, &cmd, 1);
    return ret;
}