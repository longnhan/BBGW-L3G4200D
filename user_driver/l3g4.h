#ifndef __GYRO_L3G4200_H__
#define __GYRO_L3G4200_H__

#include <linux/i2c-dev.h>
#include <linux/mmc/ioctl.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_I2C_ADR							0x69
#define DEVICE_NAME								0x0F
#define I2C_DEVICE "/dev/i2c-2"
//read and write registers
#define DEVICE_CTRL_REG_1						0x20
#define DEVICE_CTRL_REG_2						0x21
#define DEVICE_CTRL_REG_3						0x22
#define DEVICE_CTRL_REG_4						0x23
#define DEVICE_CTRL_REG_5						0x24
#define	DEVICE_REFERENCE						0x25
#define DEVICE_OUT_TEMP							0x26
#define DEVICE_STATUS_REG						0x27

#define 	DEVICE_FIFO_CTRL_REG				0x2E
#define		DEVICE_FIFO_SRC_REG					0x2F
//FIFO setup mode
#define 	DEVICE_FIFO_MODE_BYPASS				0b0001111
#define 	DEVICE_FIFO_MODE_FF					0x0011111
#define 	DEVICE_FIFO_MODE_STREAM				0x0101111
#define 	DEVICE_FIFO_MODE_STREAM_TO_FF		0x0111111
#define 	DEVICE_FIFO_MODE_BYPASS_TO_STREAM 	0x04
// 3 axises
#define		DEVICE_OUT_X_L_REG					0x28
#define		DEVICE_OUT_X_H_REG					0x29
#define		DEVICE_OUT_Y_L_REG					0x2A
#define		DEVICE_OUT_Y_H_REG					0x2B
#define		DEVICE_OUT_Z_L_REG					0x2C
#define		DEVICE_OUT_Z_H_REG					0x2D

enum deviceOperationMode
{
	Device_Mode_Normal,
	Device_Mode_Sleep,
	Device_Mode_Shutdown
};

enum bufferOperationMode
{
	Buffer_Mode_Bypass,
	Buffer_Mode_FIFO,
	Buffer_Mode_Stream,
	Buffer_Mode_Bypass_2_Stream,
	Stream_2_FIFO
};

extern void i2cInit(void);
extern uint8_t getI2cData(uint8_t deviceAddress, uint8_t regAddress, uint8_t *buf);
extern uint8_t sendI2cData(uint8_t deviceAddress, uint8_t regAddress, uint8_t cmd);

#endif