#include "l3g4.h"

uint8_t readDeviceName(uint8_t *ptr)
{
    getI2cData(DEVICE_NAME, ptr, 1);
    printf("devce name: 0x%x\n", ptr[0]);
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
	}
    sendI2cData(DEVICE_CTRL_REG_1, send_Ctrl_Reg1);
    usleep(350000);
    getI2cData(DEVICE_CTRL_REG_1, &read_Ctrl_Reg1, 1);
	return ret;
}

uint8_t read_X_Axis(int16_t *ptr)
{

}

uint8_t read_Y_Axis(int16_t *ptr)
{

}

uint8_t read_Z_Axis(int16_t *ptr)
{

}