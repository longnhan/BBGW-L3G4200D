#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include "main.h"

/*system i2c config*/
int i2c_File;
char i2c_Device[]="/dev/i2c-2";
uint8_t device_Address = 0x69;
enum deviceOperationMode device_Mode = Device_Mode_Normal;

int main(void)
{
    uint8_t buf[1]={0};
    int8_t temp=0;
    int16_t xAxis = 0;
    int16_t yAxis = 0; 
    int16_t zAxis = 0;

    i2cInit();
    setDeviceMode(device_Mode);
    while(1)
    {
        usleep(100000);
        readTemperature(&temp);
        printf("device temperature: %d\n", temp);
        readDeviceName(buf);
        printf("device name: 0x%x\n", buf[0]);
        read_X_Axis(&xAxis);
        read_Y_Axis(&yAxis);
        read_Z_Axis(&zAxis);
        printf("X axis: %d |Y axis: %d|Z axis: %d\n",xAxis, yAxis, zAxis);
    }
    return 0;    
}