#include "i2c_driver.h"

uint8_t i2cInit(void)
{
    char filename[20];

    // Open the I2C bus
    sprintf(filename, "%s", i2c_Device);
    if ((i2c_File = open(filename, O_RDWR)) < 0) 
    {
        perror("Failed to open the bus.");
        return 1;
    }
    // Set the I2C slave address
    if (ioctl(i2c_File, I2C_SLAVE, device_Address) < 0) 
    {
        perror("Failed to acquire bus access and/or talk to slave.");
        return 1;
    }
    
    return 0;
}
void i2cClose(void)
{
    close(i2c_File);
}
uint8_t getI2cData(uint8_t regAddress, uint8_t *buf, uint8_t size)
{
    uint8_t ret = 0;
    write(i2c_File, &regAddress, 1);
    ret = read(i2c_File, buf, size);
    return ret;
}
uint8_t sendI2cData(uint8_t regAddress, uint8_t cmd)
{
    uint8_t ret = 0;
    write(i2c_File, &regAddress, 1);
    ret = write(i2c_File, &cmd, 1);
    return ret;
}