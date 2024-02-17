#ifndef __I2C_DRIVER_H__
#define __I2C_DRIVER_H__

#include <linux/i2c-dev.h>
#include <linux/mmc/ioctl.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

extern int i2c_File;
extern char i2c_Device[];
extern uint8_t device_Address;

extern uint8_t i2cInit(void);
extern void i2cClose(void);
extern uint8_t getI2cData(uint8_t regAddress, uint8_t *buf, uint8_t size);
extern uint8_t sendI2cData(uint8_t regAddress, uint8_t cmd);

#endif /*__I2C_DRIVER_H__*/