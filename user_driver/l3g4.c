#include "l3g4.h"

uint8_t readDeviceName(uint8_t *ptr)
{
    getI2cData(DEVICE_NAME, ptr, 1);
}

uint8_t readTemperature(int8_t *ptr)
{
    uint8_t ret=0;
    uint8_t buf[1] = {0};
    ret = getI2cData(DEVICE_OUT_TEMP, buf, 1);
    *ptr = (int8_t)buf;
    return ret;
}

uint8_t setDeviceMode(enum deviceOperationMode device_Mode)
{
    uint8_t read_Ctrl_Reg1=0;
	uint8_t send_Ctrl_Reg1=0;
    getI2cData(DEVICE_CTRL_REG_1, &read_Ctrl_Reg1, 1);
    uint8_t _pdBit= (read_Ctrl_Reg1 >> 3) & 0x1;
    uint8_t ret=0;
	switch (device_Mode)
	{
	case Device_Mode_Normal:
		if(_pdBit == 0)
		{
			send_Ctrl_Reg1 = read_Ctrl_Reg1 | 0b00001001;
		}
		else
		{
			send_Ctrl_Reg1 = read_Ctrl_Reg1 & 0xFF;
		}
		break;
	case Device_Mode_Sleep:
		if(_pdBit == 0)
		{
			send_Ctrl_Reg1 = (read_Ctrl_Reg1 | 0b00001000) & 0b11111000;
		}
		else
		{
			send_Ctrl_Reg1 = read_Ctrl_Reg1 & 0b11111000;
		}
		break;
	case Device_Mode_Shutdown:
		send_Ctrl_Reg1 = read_Ctrl_Reg1 & 0b11110111;
		break;
	default:
		break;
	}
    sendI2cData(DEVICE_CTRL_REG_1, send_Ctrl_Reg1);
    usleep(350000);
    getI2cData(DEVICE_CTRL_REG_1, &read_Ctrl_Reg1, 1);
	return ret;
}

uint8_t read_X_Axis(int16_t *ptr)
{
    uint8_t isXAvailable=0;
	uint8_t isXOverrun=0;
	uint8_t upperData=0;
	uint8_t lowerData=0;
    uint8_t ret = 0;
	//check if X-axis data is available
	getI2cData(DEVICE_STATUS_REG, &isXAvailable, 1);
    isXAvailable = isXAvailable & 0x1;
	// check when overrun occurs
    getI2cData(DEVICE_STATUS_REG, &isXOverrun, 1);
	isXOverrun = (isXOverrun & 0x10) >>4;
	
    if((isXAvailable == 1) && (isXOverrun == 1))
	{
		getI2cData(DEVICE_OUT_X_H_REG, &upperData, 1);
		getI2cData(DEVICE_OUT_X_L_REG, &lowerData, 1);
		//data proccessing
		*ptr = (int16_t)(((uint16_t)upperData << 8) | (uint16_t)lowerData);

	}
    else
    {
        ret = 1;
    }
	return ret;
}

uint8_t read_Y_Axis(int16_t *ptr)
{
    uint8_t isYAvailable=0;
	uint8_t isYOverrun=0;
	uint8_t upperData=0;
	uint8_t lowerData=0;
    uint8_t ret = 0;
	//check if Y-axis data is available
	getI2cData(DEVICE_STATUS_REG, &isYAvailable, 1);
    isYAvailable = (isYAvailable & 0x2) >> 1;
	// check when overrun occurs
    getI2cData(DEVICE_STATUS_REG, &isYOverrun, 1);
	isYOverrun = (isYOverrun & 0x20) >>5;
	
    if((isYAvailable == 1) && (isYOverrun == 1))
	{
		getI2cData(DEVICE_OUT_Y_H_REG, &upperData, 1);
		getI2cData(DEVICE_OUT_Y_L_REG, &lowerData, 1);
		//data proccessing
		*ptr = (int16_t)(((uint16_t)upperData << 8) | (uint16_t)lowerData);

	}
    else
    {
        ret = 1;
    }
	return ret;
}

uint8_t read_Z_Axis(int16_t *ptr)
{
    uint8_t isZAvailable=0;
	uint8_t isZOverrun=0;
	uint8_t upperData=0;
	uint8_t lowerData=0;
    uint8_t ret = 0;
	//check if Z-axis data is available
	getI2cData(DEVICE_STATUS_REG, &isZAvailable, 1);
    isZAvailable = (isZAvailable & 0x4) >> 2;
	// check when overrun occurs
    getI2cData(DEVICE_STATUS_REG, &isZOverrun, 1);
	isZOverrun = (isZOverrun & 0x40) >>6;
	
    if((isZAvailable == 1) && (isZOverrun == 1))
	{
		getI2cData(DEVICE_OUT_Z_H_REG, &upperData, 1);
		getI2cData(DEVICE_OUT_Z_L_REG, &lowerData, 1);
		//data proccessing
		*ptr = (int16_t)(((uint16_t)upperData << 8) | (uint16_t)lowerData);

	}
    else
    {
        ret = 1;
    }
	return ret;
}