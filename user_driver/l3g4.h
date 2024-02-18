#ifndef __GYRO_L3G4200_H__
#define __GYRO_L3G4200_H__

#include "i2c_driver.h"

#define DEVICE_I2C_ADR						0x69
#define DEVICE_NAME							0x0F

//read and write registers
#define DEVICE_CTRL_REG_1					0x20
#define DEVICE_CTRL_REG_2					0x21
#define DEVICE_CTRL_REG_3					0x22
#define DEVICE_CTRL_REG_4					0x23
#define DEVICE_CTRL_REG_5					0x24
#define	DEVICE_REFERENCE					0x25
#define DEVICE_OUT_TEMP						0x26
#define DEVICE_STATUS_REG					0x27

#define DEVICE_FIFO_CTRL_REG				0x2E
#define	DEVICE_FIFO_SRC_REG					0x2F
//FIFO setup mode
#define DEVICE_FIFO_MODE_BYPASS				0b0001111
#define DEVICE_FIFO_MODE_FF					0x0011111
#define DEVICE_FIFO_MODE_STREAM				0x0101111
#define DEVICE_FIFO_MODE_STREAM_TO_FF		0x0111111
#define DEVICE_FIFO_MODE_BYPASS_TO_STREAM 	0x04
// 3 axises
#define	DEVICE_OUT_X_L_REG					0x28
#define	DEVICE_OUT_X_H_REG					0x29
#define	DEVICE_OUT_Y_L_REG					0x2A
#define	DEVICE_OUT_Y_H_REG					0x2B
#define	DEVICE_OUT_Z_L_REG					0x2C
#define	DEVICE_OUT_Z_H_REG					0x2D

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

extern uint8_t readDeviceName(uint8_t *ptr);
extern uint8_t readTemperature(int8_t *ptr);
extern uint8_t setDeviceMode(enum deviceOperationMode device_Mode);
extern uint8_t read_X_Axis(int16_t *ptr);
extern uint8_t read_Y_Axis(int16_t *ptr);
extern uint8_t read_Z_Axis(int16_t *ptr);

#endif /*__GYRO_L3G4200_H__*/